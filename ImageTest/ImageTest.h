#pragma once
#include "Resource.h"
#include "Sprite.h"

int x, y, w, h;
DWORD globalTime = 0;
HBITMAP sheet;
Sprite barrel;
Sprite boom;

inline HBITMAP LoadBmp(HINSTANCE hInst, int ID) {
	return (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(ID), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}
inline void updateWindowDimensions(HWND hWnd) {
	RECT window;
	GetWindowRect(hWnd, &window);
	x = window.left;
	y = window.top;
	w = window.right - x;
	h = window.bottom - y;
}

void start() {
	
}
void paint(HDC &hdc) {
	HDC hdcMem = CreateCompatibleDC(hdc);
	
	int loop = 90;
	int amp = 90;
	double angle = tau / loop;
	rotate(boom.x, boom.y, w * 2 / 5, h * 2 / 5, -angle);
	rotate(barrel.x, barrel.y, boom.x, boom.y, angle);

	barrel.nextFrame(hdc, hdcMem);
	boom.nextFrame(hdc, hdcMem);

	boom.paint(hdc, hdcMem);
	barrel.paint(hdc, hdcMem);

	DeleteDC(hdcMem);
}
void CALLBACK tick(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	InvalidateRect(hwnd, NULL, true);
	globalTime++;
}
void init(HWND hWnd, HINSTANCE hInst) {
	SetTimer(hWnd, NULL, 1000 / 24, tick);
	updateWindowDimensions(hWnd);

	sheet = LoadBmp(hInst, IDB_EXPLOSION);
	SpriteSheet sprites(sheet, 0, 20, 20, 8, 4);

	boom = Sprite(sprites, w / 2, h / 2, 8);
	sprites.loopID++;
	barrel = Sprite(sprites, 0, 0, 4);
}
