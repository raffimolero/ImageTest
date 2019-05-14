#pragma once

#include "resource.h"
#include "Sprite.h"

HBITMAP image;
Sprite numbers;

void paint(HDC hdc) {
	HDC hdcMem = CreateCompatibleDC(hdc);
	HPEN pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	SelectObject(hdc, pen);

	numbers.nextFrame();
	numbers.paint(hdc, hdcMem);

	MoveToEx(hdc, 100, 100, NULL);
	LineTo(hdc, 50, 100);
	DeleteDC(hdcMem);
}
