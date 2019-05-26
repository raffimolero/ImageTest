#include "stdafx.h"
#include "Color.h"

int hueWave(unsigned char val) {
	if (val > 128) val = -val;
	int ret = (val & 255) * 6;
	ret -= 256;
	ret = ret > 256 ? 256 :
		ret < 0 ? 1 :
		ret;
	return -ret & 255;
}
COLORREF hue(int val) {
	int r = hueWave(val);
	int g = hueWave(val - 256 / 3);
	int b = hueWave(val + 256 / 3);
	return RGB(r, g, b);
}
