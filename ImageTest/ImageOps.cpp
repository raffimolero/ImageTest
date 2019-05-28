#include "stdafx.h"
#include "ImageOps.h"

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

HBITMAP crop(HDC hdc, HBITMAP hbm, int l, int t, int w, int h) {
	BITMAP bm = getData(hbm);
	char* source = getPixelData(hdc, hbm);
	char* cropped = new char[w * h * 3];

	char r, g, b;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			getPixel(source, bm.bmWidth, x + l, y + t, r, g, b);
			setPixel(cropped, w, x, y, r, g, b);
		}
	}

	BITMAPINFO bmInf = createBmInf(w, h);
	HBITMAP ret = CreateCompatibleBitmap(hdc, w, h);
	setPixelData(hdc, ret, bmInf, cropped);
	delete[] cropped;
	delete[] source;
	return ret;
}
