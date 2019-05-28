#pragma once
#include <math.h>

const double tau = 6.283185307179586;

inline POINT toPoint(int x, int y);
inline void vecToCoords(double &x, double &y, double length, double angle);
inline double dstTo(double x, double y);
inline double dirTo(double x, double y);
inline void rotate(double &x, double &y, POINT c, double angle);
