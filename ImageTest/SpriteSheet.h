#pragma once
#include <stdarg.h>

class SpriteSheet
{
private:
public:
	HBITMAP sheet;
	int w, h;
	int frame = 0, loopID = 0, loopCount;
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

