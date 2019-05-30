#pragma once
#include "Resource.h"
#include "Sprite.h"
#include "ImageOps.h"

RECT window;
int x, y, w, h;
int id = 0;
bool update = false;
DWORD globalTime = 0;
HBITMAP sheet;
Sprite barrel;
Sprite boom;

inline HBITMAP LoadBmp(HINSTANCE hInst, int ID) {
	return (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(ID), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}
inline void updateWindowDimensions(HWND hWnd) {
	GetWindowRect(hWnd, &window);
	x = window.left;
	y = window.top;
	w = window.right - x;
	h = window.bottom - y;
}

void start() {}
void paint(HDC &hdc) {
	HDC buf = CreateCompatibleDC(hdc);
	HDC mem = CreateCompatibleDC(hdc);
	HBITMAP bufBmp = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(buf, bufBmp);

	fillSolidRect(buf, 0, 0, w, h, hue(globalTime));

	barrel.paint(buf, mem);
	boom.paint(buf, mem);

	DeleteDC(mem);
	BitBlt(hdc, 0, 0, w, h, buf, 0, 0, SRCCOPY);
	DeleteObject(bufBmp);
	DeleteDC(buf);
}
void CALLBACK tick(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	if (globalTime % 4 == 0) {
		barrel.nextFrame();
		boom.nextFrame();
	}

	double angle = tau / 256;
	rotate(boom.x, boom.y, w * 2 / 5, h * 2 / 5, -angle);
	rotate(barrel.x, barrel.y, boom.x, boom.y, angle);
	
	InvalidateRect(hwnd, NULL, false);
	globalTime++;
}
void init(HWND hWnd, HINSTANCE hInst) {
	SetTimer(hWnd, NULL, 15, tick);
	updateWindowDimensions(hWnd);

	sheet = LoadBmp(hInst, IDB_EXPLOSION);
	SpriteSheet sprites(sheet, 0, 20, 20, 8, 4);

	boom = Sprite(sprites, w / 2, h / 2, 8);
	sprites.loopID++;
	barrel = Sprite(sprites, 0, 0, 4);
}
