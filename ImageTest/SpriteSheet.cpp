#include "stdafx.h"
#include "SpriteSheet.h"


SpriteSheet::SpriteSheet()
{
}
SpriteSheet::SpriteSheet(HBITMAP &content, int loopLength, int width, int height)
{
	sheet = content;
	loopLen = loopLength;
	w = width;
	h = height;
}
SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::paint(HDC hdc, HDC mem, int x, int y) {
	SelectObject(mem, sheet);
	BitBlt(hdc, x, y, w, h, mem, frame * w, 0, SRCCOPY);
}

void SpriteSheet::nextFrame() {
	frame++;
	frame %= loopLen;
}
