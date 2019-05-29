#pragma once
#include "SpriteSheet.h"

class Sprite
{
public:
	SpriteSheet sprites;
	double x, y, w, h;
	double stretchX = 1, stretchY = 1;

	Sprite();
	Sprite(
		SpriteSheet &spriteSheet,
		int left, int top,
		double stretch
	);
	~Sprite();

	void paint(HDC hdc, HDC mem);
	bool nextFrame(HDC hdc, HDC mem);
};

