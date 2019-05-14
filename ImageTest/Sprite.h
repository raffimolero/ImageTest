#pragma once
#include "SpriteSheet.h"
class Sprite
{
public:
	SpriteSheet sprites;
	int x, y, w, h;

	Sprite();
	Sprite(SpriteSheet &spriteSheet, int left, int top);
	~Sprite();

	void paint(HDC hdc, HDC mem);
	bool nextFrame();
};

