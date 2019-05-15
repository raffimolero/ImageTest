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
bool Sprite::nextFrame() {
	return sprites.nextFrame();
}
