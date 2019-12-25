#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;


template <typename Cell = double>
class Matrix
{
private:
	int rows;
	int columns;
	Cell **cells;
	void AllocateCells(int, int);
	void FreeCells();
public:
	Matrix() : rows(0), columns(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int, int);							// Конструктор нулевой матрицы
	Matrix(int, int, Cell*);						// Конструктор матрицы из списка
	~Matrix();								// Деструктор

	Cell &operator()(int i, int j) { return cells[i-1][j-1]; }

	Matrix<Cell> transpos()
	{
		Matrix<Cell> newMatrix = Matrix(columns, rows);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				newMatrix.cells[j][i] = cells[i][j];

		return newMatrix;
	};
	
	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц
	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
	int getRows() {
		return rows;
	}
};


template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.rows, M.columns);
	for (int i=0; i<rows; i++)
		for (int j=0; j<columns; j++)
			cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int rows, int columns)
{
	AllocateCells(rows, columns);
	for (int i=0; i<rows; i++)
		for (int j=0; j<columns; j++)
			cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int rows, int columns, Cell* list)
{
	AllocateCells(rows, columns);
	int j = 0;
	int idx = 0;
	while (j < rows){
		for(int i = 0; i < columns; i++){
			cells[j][i] = list[idx++];
		}
		j++;
	}
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if ( rows != M.rows || columns != M.columns)
	{
		FreeCells();
		AllocateCells(M.rows, M.columns);
	}

	for (int i=0; i<rows; i++)
		for (int j=0; j<columns; j++)
			cells[i][j] = M.cells[i][j];

	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && columns == M.columns)
	{
		for (int i=0; i<rows; i++)
			for (int j=0; j<columns; j++)
				res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && columns == M.columns)
	{
		for (int i=0; i<rows; i++)
			for (int j=0; j<columns; j++)
			res.cells[i][j] -= M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	Matrix<Cell> res(rows, M.columns);
	if (columns == M.rows )
	{
		for (int i=0; i<rows; i++)
			for (int j=0; j<M.columns; j++)
			{	
				for(int k=0; k < columns; ++k){
					res.cells[i][j] += cells[i][k] * M.cells[k][j];
				}
			}
	}
	return res;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int rows, int columns)
{
	cells = new Cell*[rows];
	for (int i=0; i<rows; i++)
		cells[i] = new Cell[columns];
	this->rows = rows;
	this->columns = columns;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i=0; i<rows; i++)
		delete cells[i];
	delete cells;
	this->rows = 0;
	this->columns = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i=0; i<M.rows; i++)
		for (int j=0; j<M.columns; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i=0; i<M.rows; i++)
	{
		fo << "  ";
		for (int j=0; j<M.columns; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}



#endif MATRIX_H
