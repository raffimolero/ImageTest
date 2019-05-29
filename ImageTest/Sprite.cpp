#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite()
{
}
Sprite::Sprite(
	SpriteSheet &spriteSheet,
	int left, int top,
	double stretch) {
	sprites = spriteSheet;
	x = left;
	y = top;
	w = sprites.w;
	h = sprites.h;
	stretchX = stretchY = stretch;
}
Sprite::~Sprite()
{
}

void Sprite::paint(HDC hdc, HDC mem) {
	sprites.paint(
		hdc, mem,
		x - w * stretchX / 2, y - h * stretchY / 2,
		stretchX, stretchY
	);
}
bool Sprite::nextFrame(HDC hdc, HDC mem) {
	bool ret = sprites.nextFrame();
	sprites.frame = cropBmp(
		hdc, mem,
		sprites.sheet,
		sprites.frameNum * w,
		sprites.loopID * h,
		w, h
	);
	return ret;
}
