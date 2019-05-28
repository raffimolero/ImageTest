#include "stdafx.h"
#include "EuclideanOps.h"

inline POINT toPoint(int x, int y) {
	POINT ret;
	ret.x = x;
	ret.y = y;
	return ret;
}
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
