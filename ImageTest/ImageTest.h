#pragma once
#include "resource.h"
#include <math.h>

#include "Sprite.h"

const double tau = 6.283185307179586;
HBITMAP image;
Sprite barrel;

void paint(HDC hdc) {
	HDC hdcMem = CreateCompatibleDC(hdc);
	SpriteSheet *sprites = &barrel.sprites;
	int id = sprites->loopID;
	int loopLen = sprites->loopLens[id];
	int frame = sprites->frame;

	if (barrel.nextFrame()) {
		sprites->loopID++;
		sprites->loopID %= sprites->loopCount;
	}
	barrel.paint(hdc, hdcMem);

	int x = 100, y = 100;
	MoveToEx(hdc, x, y, NULL);
	HPEN pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	SelectObject(hdc, pen);

	
	double angle = tau / loopLen * frame;
	int len = 50;

	int xTo = sin(angle) * len;
	int yTo = cos(angle) * len;

	LineTo(hdc, x + xTo, y + yTo);
	DeleteDC(hdcMem);
}
