#pragma once
class Sprite
{
private:
	HBITMAP img;

	void drawImage(HDC hdc, int srcX, int srcY);
public:
	int x, y, w, h;
	int frame = 0;

	Sprite();
	Sprite(HBITMAP &image, int left, int top, int width, int height);
	~Sprite();

	void paint(HDC hdc);
};

