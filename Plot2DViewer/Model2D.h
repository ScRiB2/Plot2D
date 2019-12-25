#ifndef MODEL_2D_H
#define MODEL_2D_H
#include <string>
#include "Matrix.h"
#include "AffineTransform.h"

class Model2D
{
	private:
		Matrix<> CumulativeAT;
		Matrix<> Vertices;
		Matrix<> InitialVertices;
		Matrix<int> Edges;
	public:
		Model2D() : Vertices(), Edges() {}
		Model2D(const Matrix<> Vertices, const Matrix<int> Edges):Vertices(Vertices), Edges(Edges), 
			CumulativeAT(Identify()), InitialVertices(Vertices) {}
		Matrix<> GetVertices() { return Vertices; }
		Matrix<int> GetEdges() { return Edges; }

		double GetVertexX(int index) 
		{
			return Vertices(index, 1) / Vertices(index, 3);
		}

		double GetVertexY(int index) 
		{
			return Vertices(index, 2) / Vertices(index, 3);
		}

		void Apply(Matrix<> transform) 
		{
			CumulativeAT = transform * CumulativeAT;
			Vertices = InitialVertices * CumulativeAT.transpos();

		}
};
#endif MODEL_2D_H