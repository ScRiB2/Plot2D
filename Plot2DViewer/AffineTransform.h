#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H
#include <math.h>
Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1};
	return Matrix<>(3, 3, T);
}

Matrix<> Rotation(double t)
{
	double T[9] = {
		cos(t), -sin(t), 0,
		sin(t), cos(t), 0,
		0, 0, 1};
	return Matrix<>(3, 3, T);
}
Matrix<> Scaling(double kx, double ky)
{	double T[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1};
	return Matrix<>(3, 3, T);
}
Matrix<> Identify()
{	
	double T[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1};
	return Matrix<>(3, 3, T);
}

Matrix<> Rotation(double c, double s)
{	double inter = 1 / sqrt(c*c + s*s);
	double T[9] = {
		inter * c, -inter * s, 0,
		inter * s, inter * c, 0,
		0, 0, 1};
	return Matrix<>(3, 3, T);
}

Matrix<> Reflection(double x1, double x2, double y1, double y2)
{
	double a = y1 - y2;
	double b = x2 - x1;
	double c = x1* y2 - x2 * y1;

	double inter = 1 / (a * a + b * b);
	double T[9] = {
		inter * (b*b - a*a), inter * (-2*a*b), inter * (-2*a*c),
		inter * (-2*a*b), inter * (a*a - b*b), inter * (-2*b*c),
		0, 0, inter * (a*a + b*b) };
	return Matrix<>(3, 3, T);
}

// Здесь требуется реализовать функции, возвращающие матрицы базовых АП:
// Rotation(c, s) - поворот на угол, косинус и синус которого пропорциональны величинам c и s;

// В приведённом примере используется конструктор матрицы из списка.
// Приветствуются идеи о других способах создания матриц.
// Например, вызов функции, создающей единичную матрицу,
// с последующим переопределением некоторых её коэффициентов.

#endif AFFINE_TRANSFORM_H
