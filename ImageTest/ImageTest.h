#pragma once
#include "Resource.h"
#include "Sprite.h"

DWORD globalTime = 0;
HBITMAP sheet;
Sprite barrel;
Sprite boom;

inline HBITMAP LoadBmp(HINSTANCE hInst, int ID) {
	return (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(ID), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}

void start() {
	
}
void paint(HDC &hdc) {
	HDC hdcMem = CreateCompatibleDC(hdc);
	
	barrel.nextFrame(hdc);
	barrel.paint(hdc, hdcMem);

	int loop = 180;
	int amp = 90;
	double angle = tau / loop;
	POINT c = toPoint(100, 100);
	rotate(boom.x, boom.y, c, angle);

	boom.nextFrame(hdc);
	boom.paint(hdc, hdcMem);

	DeleteDC(hdcMem);
}
void CALLBACK tick(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	InvalidateRect(hwnd, NULL, true);
	globalTime++;
}
void init(HWND hWnd, HINSTANCE hInst) {
	SetTimer(hWnd, NULL, 1000 / 24, tick);
	sheet = LoadBmp(hInst, IDB_EXPLOSION);
	SpriteSheet sprites(sheet, 0, 20, 20, 4, 8);
	barrel = Sprite(sprites, 10, 10, 4);
	sprites.loopID++;
	boom = Sprite(sprites, 100, 10, 8);
}
