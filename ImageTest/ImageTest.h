#pragma once

#include "resource.h"
#include "Sprite.h"

HBITMAP image;
Sprite numbers;

void paint(HDC hdc) {
	numbers.paint(hdc);

	/*HDC hdcMem = CreateCompatibleDC(hdc);
	HGDIOBJ oldBmp = SelectObject(hdcMem, image);
	BITMAP bmp;
	GetObject(image, sizeof(bmp), &bmp);
	BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, oldBmp);
	DeleteDC(hdcMem);*/
}
