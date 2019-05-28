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
		x, y,
		stretchX, stretchY
	);
}
bool Sprite::nextFrame(HDC hdc) {
	bool ret = sprites.nextFrame();
	sprites.frame = crop(hdc, sprites.sheet, sprites.frameNum * w, (sprites.loopCount - sprites.loopID - 1) * h, w, h);
	return ret;
}
