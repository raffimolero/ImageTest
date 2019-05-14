#pragma once
#include "resource.h"
#include <math.h>

#include "Sprite.h"

const double tau = 6.283185307179586;
int globalTimer = 0;
Sprite barrel;
Sprite boom;

void paint(HDC hdc) {
	HDC hdcMem = CreateCompatibleDC(hdc);

	barrel.nextFrame();
	barrel.paint(hdc, hdcMem);

	int loop = 180;
	int amp = 90;
	boom.x = 100 + (sin(tau / loop * (globalTimer % loop)) * amp);

	boom.nextFrame();
	boom.paint(hdc, hdcMem);

	DeleteDC(hdcMem);
	globalTimer++;
}
