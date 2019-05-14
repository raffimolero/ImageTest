#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}
Sprite::Sprite(HBITMAP &image, int left, int top, int width, int height) {
	x = left;
	y = top;
	w = width;
	h = height;
	img = image;
}
Sprite::~Sprite()
{
}

void Sprite::drawImage(HDC hdc, int srcX, int srcY) {
	HDC hdcMem = CreateCompatibleDC(hdc);
	HGDIOBJ oldBmp = SelectObject(hdcMem, img);
	BITMAP bmp;
	GetObject(img, sizeof(bmp), &bmp);
	BitBlt(hdc, x, y, w, h, hdcMem, srcX, srcY, SRCCOPY);
	SelectObject(hdcMem, oldBmp);
	DeleteDC(hdcMem);
}

void Sprite::paint(HDC hdc) {
	drawImage(hdc, 0, 0);
}
