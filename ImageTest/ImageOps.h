#pragma once
#include "ColorOps.h"
#include "EuclideanOps.cpp"
#include <Windows.h>
#include <wingdi.h>

inline BITMAPINFOHEADER createBmInfH(BITMAP bm);
inline BITMAPINFO createBmInf(BITMAP bm);
inline BITMAPINFO createBmInf(int w, int h);
inline BITMAP getData(HBITMAP hbm);
inline void getPixel(char* data, int w, int x, int y, char &r, char &g, char &b);
inline void setPixel(char* &data, int w, int x, int y, char r, char g, char b);

char* getPixelData(HDC hdc, HBITMAP hbm);
void setPixelData(HDC hdc, HBITMAP &hbm, BITMAPINFO bmInf, char* data);

HBITMAP crop(HDC hdc, HBITMAP hbm, int l, int t, int w, int h);
