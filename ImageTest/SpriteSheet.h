#pragma once
#include <stdarg.h>
#include "ImageOps.h"

class SpriteSheet
{
private:
public:
	HBITMAP sheet, frame;
	bool updated = false;
	int w, h;
	int frameNum = 0, loopID = 0, loopCount;
	int* loopLens;

	SpriteSheet();
	SpriteSheet(
		HBITMAP &content,
		int animationID,
		int width, int height,
		...
	);
	~SpriteSheet();

	void paint(
		HDC hdc, HDC mem,
		int x, int y,
		double stretchX,
		double stretchY
	);
	bool nextFrame();
};

