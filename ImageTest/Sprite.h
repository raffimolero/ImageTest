#pragma once
#include "SpriteSheet.h"
class Sprite
{
private:
	SpriteSheet sprites;
	HGDIOBJ old;
public:
	int x, y, w, h;
	int frame = 0, loopLen = 1;

	Sprite();
	Sprite(SpriteSheet &spriteSheet, int left, int top);
	~Sprite();

	void paint(HDC hdc, HDC mem);
	void nextFrame();
};

