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

	BITMAP bm = getData(content);
	loopCount = bm.bmHeight / h;

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
	double stretchX,
	double stretchY) {
	SelectObject(mem, frame);
	COLORREF alpha = RGB(128, 128, 128);
	TransparentBlt(
		hdc,
		x, y,
		w * stretchX, w * stretchY,
		mem,
		0, 0, w, h,
		alpha
	);
}

bool SpriteSheet::nextFrame() {
	int loopLen = loopLens[loopID];
	frameNum++;
	frameNum %= loopLen;
	return !frameNum;
}
