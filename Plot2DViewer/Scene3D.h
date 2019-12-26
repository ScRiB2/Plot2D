#ifndef SCENE_3D_H
#define SCENE_3D_H

#include "Camera2D.h"
#include <cmath>
#include <iostream>
#include "Model3D.h"

class Scene3D : public Camera2D
{
private:
	typedef double(*Func)(double);
	typedef double(*Func2)(double, double);
public:
	Model3D model;
	Scene3D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
		double v[32] = { 0, 0, 0, 1, 2, 0, 0, 1, 2, 2, 0, 1, 0, 2, 0, 1, 0, 0, 2, 1, 2, 0, 2, 1, 2, 2, 2, 1, 0, 2, 2, 1 };
		Matrix<> V(8, 4, v);
		int e[24] = { 1, 2, 2, 3, 3, 4, 4, 1, 5, 6, 6, 7, 7, 8, 8, 5, 1, 5, 2, 6, 3, 7, 4, 8 };
		Matrix<int> E(12, 2, e);
		Model3D model(V, E);
		this->model = model;
	}

	void Render(HDC dc, bool axes = true) {
		if (axes)
			Axes(dc);

		Matrix<int> edges = model.GetEdges();
		Matrix<> vertices = model.GetProjectedVertices();
		for (int i = 1; i <= edges.getRows(); i++) {
			MoveTo(model.GetVertexX(edges(i, 1)), model.GetVertexY(edges(i, 1)));
			LineTo(dc, model.GetVertexX(edges(i, 2)), model.GetVertexY(edges(i, 2)));
		}
	}
};

#endif SCENE_3D_H
