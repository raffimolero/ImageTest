#pragma once
class SpriteSheet
{
private:
public:
	HBITMAP sheet;
	int w, h;
	int frame, loopLen;

	SpriteSheet();
	SpriteSheet(HBITMAP &content, int loopLength, int width, int height);
	~SpriteSheet();

	void paint(HDC hdc, HDC mem, int x, int y);
	void nextFrame();
};

