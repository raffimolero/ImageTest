#include "stdafx.h"
#include "SpriteSheet.h"

void append(int* &arr, int len, int arg) {
	int* temp = new int[len + 1];
	for (int i = 0; i < len; i++) temp[i] = arr[i];
	temp[len] = arg;
	arr = temp;
}

SpriteSheet::SpriteSheet() {
}
SpriteSheet::SpriteSheet(
	HBITMAP &content,
	int animationID,
	int width, int height,
	...) {
	sheet = content;
	loopID = animationID;
	w = width;
	h = height;

	BITMAP bmp;
	GetObject(content, sizeof(BITMAP), &bmp);
	loopCount = bmp.bmHeight / h;

	va_list vl;
	va_start(vl, height);
	loopLens = new int[loopCount];
	for (int i = 0; i < loopCount; i++) loopLens[i] = va_arg(vl, int);
	va_end(vl);
}
SpriteSheet::~SpriteSheet() {
}

void SpriteSheet::paint(
	HDC hdc, HDC mem,
	int x, int y,
	double stretchX, double stretchY) {
	SelectObject(mem, sheet);
	StretchBlt(
		hdc,
		x, y,
		w * stretchX, h * stretchY,
		mem,
		frame * w, loopID * h,
		w, h,
		SRCCOPY);
}

bool SpriteSheet::nextFrame() {
	int loopLen = loopLens[loopID];
	frame++;
	frame %= loopLen;
	return !frame;
}
