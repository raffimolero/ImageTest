#include "stdafx.h"
#include "SpriteSheet.h"


SpriteSheet::SpriteSheet() {
}
SpriteSheet::SpriteSheet(HBITMAP &content, int* loopLengths, int animationID, int width, int height) {
	sheet = content;
	loopID = animationID;
	w = width;
	h = height;

	BITMAP bmp;
	GetObject(content, sizeof(BITMAP), &bmp);

	loopLens = loopLengths;
	loopCount = bmp.bmHeight / h;
}
SpriteSheet::~SpriteSheet() {
}

void SpriteSheet::paint(HDC hdc, HDC mem, int x, int y) {
	SelectObject(mem, sheet);
	BitBlt(hdc, x, y, w, h, mem, frame * w, loopID * h, SRCCOPY);
}

bool SpriteSheet::nextFrame() {
	int loopLen = loopLens[loopID];
	frame++;
	frame %= loopLen;
	return !frame;
}
