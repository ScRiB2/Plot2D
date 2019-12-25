#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include <cmath>
#include<iostream>
#include "Model2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
	typedef double (*Func2)(double, double);
public:
	Model2D model;
	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
		double v[12] = { 3,3,3,3,6,3,6,3,3,6,6,3};
		Matrix<> V(4, 3, v);
		int e[8] = { 1,2,2,4,4,3,3,1 };
		Matrix<int> E(4, 2, e);
		Model2D model(V, E);
		this->model = model;
	}
	void Plot(HDC dc, Func f, bool axes=true)
	{
		if (axes)
			Axes(dc);

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
		double h = 1/px;
		/*MoveTo(L()+ previousX, f(L()+ previousY));
		for(double i = L(); i < R(); i= i + h){
			LineTo(dc, i + previousX, f(i+ previousY));
		}*/
		MoveTo(L(), f(L()));
		for(double i = L(); i < R(); i= i + h){
			LineTo(dc, i, f(i));
		}
	}

	void ParametricPlot(HDC dc, Func2 fX, Func2 fY, bool axes=true)
	{
		if (axes)
			Axes(dc);

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
		double h = 1/px;
		double x = 0.0;
		double y = 0.0;
		double r = 1;
		MoveTo(fX(0, r),fY(0, r));
		for( double t = 0; t <=2 * M_PI; t+= h){
			LineTo(dc, fX(t, r), fY(t, r));
		}
		LineTo(dc, fX(2 * M_PI, r), fY(2 * M_PI, r));
	}
	void Polar(HDC dc, Func2 fX, Func2 fY, bool axes=true)
	{
		if (axes)
			Axes(dc);

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
		double h = 1/px;
		double x = 0.0;
		double y = 0.0;
		double r = 2;
		MoveTo(fX(0, r),fY(0, r));
		for( double t = 0; t <=2 * M_PI; t+= h){
			LineTo(dc, fX(t, r), fY(t, r));
		}
		LineTo(dc, fX(2 * M_PI, r), fY(2 * M_PI, r));

		r *= 2;
		MoveTo(fX(0, r),fY(0, r));
		for( double t = 0; t <=2 * M_PI; t+= h){
			LineTo(dc, fX(t, r), fY(t, r));
		}

		LineTo(dc, fX(2 * M_PI, r), fY(2 * M_PI, r));
		r *= 2;
		MoveTo(fX(M_PI/2, r),fY(0, r));
		for( double t = 0; t <=2 * M_PI; t+= M_PI/6){
			LineTo(dc, fX(t, r), fY(t, r));
			MoveTo(fX(M_PI/2, r),fY(0, r));
		}
	}

	void Render(HDC hdc) 
	{	
		Axes(hdc);

		Matrix<int> edges = model.GetEdges();
		for(int i = 1; i <= edges.getRows(); i++)
		{
			MoveTo(model.GetVertexX(edges(i, 1)), model.GetVertexY(edges(i, 1)));
			LineTo(hdc, model.GetVertexX(edges(i, 2)), model.GetVertexY(edges(i, 2)));
		}
	}
};

#endif SCENE_2D_H
