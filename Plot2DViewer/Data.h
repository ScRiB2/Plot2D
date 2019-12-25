#define _USE_MATH_DEFINES
#include <cmath>

double					// Исходные значения параметров X0, Y0, px, py
	X0=200,
	Y0=200,
	px=50,
	py=100;

double Parabola(double x)
{
	return x*x-2;
}

double Sinusoid(double x)
{
	return sin(x);
}

double ParametricX(double x, double r)
{
	return r*cos(x);
}

double ParametricY(double y, double r)
{
	return r*sin(y);
}
