#pragma once
#include "resource.h"
#include <math.h>

#include "Sprite.h"
#include "Color.h"

const double tau = 6.283185307179586;
int globalTimer = 0;
Sprite barrel;
Sprite boom;

inline void vecToCoords(double &x, double &y, double length, double angle) {
	x = sin(angle) * length;
	y = cos(angle) * length;
}
inline double dstTo(double x, double y) {
	return sqrt(x * x + y * y);
}
inline double dirTo(double x, double y) {
	double phi = atan(x / y);
	if (y < 0) phi += tau / 2;
	return phi;
}
inline void rotate(double &x, double &y, POINT c, double angle) {
	double xT = x - c.x;
	double yT = y - c.y;
	double dir = dirTo(xT, yT);
	double dst = dstTo(xT, yT);
	vecToCoords(x, y, dst, dir + angle);
	x += c.x;
	y += c.y;
}
inline void getPixel(char* data, int w, int x, int y, char &r, char &g, char &b) {
	int index = (x + y * w) * 3;
	r = data[index];
	g = data[index + 1];
	b = data[index + 2];
}
inline void setPixel(char* &data, int w, int x, int y, char r, char g, char b) {
	int index = (x + y * w) * 3;
	data[index] = r;
	data[index + 1] = g;
	data[index + 2] = b;
}

inline HBITMAP LoadBmp(HINSTANCE hInst, int ID) {
	return (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(ID), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}
inline BITMAPINFOHEADER createBmInfH(BITMAP bm) {
	BITMAPINFOHEADER ret;
	ret.biSize = sizeof(BITMAPINFOHEADER);
	ret.biWidth = bm.bmWidth;
	ret.biHeight = bm.bmHeight;
	ret.biPlanes = 1;
	ret.biBitCount = bm.bmBitsPixel;
	ret.biCompression = BI_RGB;
	ret.biSizeImage = (bm.bmWidth * bm.bmBitsPixel + 31) / 8 * bm.bmHeight;
	return ret;
}
inline BITMAPINFO createBmInf(BITMAP bm) {
	BITMAPINFO ret;
	ret.bmiHeader = createBmInfH(bm);
	return ret;
}
inline BITMAPINFO createBmInf(int w, int h) {
	BITMAP bm;
	bm.bmWidth = w;
	bm.bmHeight = h;
	bm.bmBitsPixel = 24;
	BITMAPINFO ret;
	ret.bmiHeader = createBmInfH(bm);
	return ret;
}
inline BITMAP getData(HBITMAP hbm) {
	BITMAP bm;
	GetObject(hbm, sizeof(BITMAP), &bm);
	return bm;
}

char* getPixelData(HDC hdc, HBITMAP hbm) {
	BITMAP bm = getData(hbm);
	BITMAPINFO bmInf = createBmInf(bm);
	char* ret = new char[bmInf.bmiHeader.biSizeImage];
	GetDIBits(hdc, hbm, 0, bm.bmHeight, ret, &bmInf, DIB_PAL_COLORS);
	return ret;
}
void setPixelData(HDC hdc, HBITMAP &hbm, BITMAPINFO bmInf, char* data) {
	BITMAP bm = getData(hbm);
	SetDIBits(hdc, hbm, 0, bmInf.bmiHeader.biHeight, data, &bmInf, DIB_PAL_COLORS);
}

void paint(HDC &hdc, RECT window) {
	//int w = window.right - window.left;
	//int h = window.bottom - window.top;

	HDC hdcMem = CreateCompatibleDC(hdc);
	//HDC hdcBuf = CreateCompatibleDC(hdcMem);
	
	if (false) {
		barrel.nextFrame();
		barrel.paint(hdc, hdcMem);

		int loop = 180;
		int amp = 90;
		double angle = tau / loop * (globalTimer % loop);
		boom.x = 100 + (sin(angle) * amp);
		boom.y = 100 + (cos(angle) * amp);

		boom.nextFrame();
		boom.paint(hdc, hdcMem);
	}
	HBITMAP hbm = barrel.sprites.sheet;
	char* pixels = getPixelData(hdc, hbm);
	BITMAP bm = getData(hbm);

	int w = 160;
	int h = 40;
	int w2 = w * 2;
	int h2 = h * 2;
	char* d = new char[w2 * h2 * 3];
	char r, g, b;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			getPixel(pixels, w, x, y, r, g, b);
			setPixel(d, w2, x * 2, y * 2, r, g, b);
			setPixel(d, w2, x * 2 + 1, y * 2, r, g, b);
			setPixel(d, w2, x * 2, y * 2 + 1, r, g, b);
			setPixel(d, w2, x * 2 + 1, y * 2 + 1, r, g, b);
		}
	}
	BITMAPINFO bmInf = createBmInf(w2, h2);
	HBITMAP temp = CreateCompatibleBitmap(hdc, w2, h2);
	setPixelData(hdc, temp, bmInf, d);
	SelectObject(hdcMem, temp);
	BitBlt(hdc, 0, 0, w2, h2, hdcMem, 0, 0, SRCCOPY);
	bmInf.bmiHeader.biHeight = h;
	bmInf.bmiHeader.biWidth = w;

	DeleteObject(temp);
	delete[] d;
	delete[] pixels;
	DeleteDC(hdcMem);

	globalTimer++;
}
