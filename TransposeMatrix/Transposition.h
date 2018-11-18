#pragma once
#include <string>
#include <iostream>

/*
	Class for matrix transposition.
*/
class MatrixTransposer
{
	public:
		MatrixTransposer(int cols);

		// actual transposition of matrix (actual PC speed test)
		template <class T> void Transpose(T* matrix, int rows, int cols);
		template <class T> void TransposeAndSwap(T* matrixA, T* matrixB, int rows, int col);
		template <class T> void TransposeAndSwapTrivially(T* matrixA, T* matrixB, int rows, int col);
		template <class T> void TransposeTrivially(T* matrix, int rows, int col);

		// generating indices of transposed elements (ideal cache simulator input generating)
		void SimulateTransposition(int side, bool trivial);
		void GenerateTransposedElements(int row, int column, int side);
		void GenerateTransposedElementsAndSwap(int rowA, int columnA, int rowB, int columnB, int rows, int cols);
		void GenerateTransposedElementsAndSwapTrivially(int rowA, int columnA, int rowB, int columnB, int rows, int cols);
		void GenerateTransposedElementsTrivially(int row, int column, int side);
		
		int trivialBound = 10;

	private:
		int columns;
};
 
#pragma region Actual transposition
/*
	Transposes given SQUARE matrix, dimensions determined by params rows and cols. Equivalent to TransposeOnDiagonal from the lecture.
*/
template <class T> void MatrixTransposer::Transpose(T* matrix, int rows, int cols)
{
	// only square matrices, ergo rows == cols
	if (rows <= trivialBound)
	{
		TransposeTrivially(matrix, rows, cols);
	}
	else
	{
		int newside = (rows / 2);
		// transpose
		Transpose(matrix, newside, newside);
		Transpose(matrix + columns*newside + newside, rows - newside, cols-newside);
		TransposeAndSwap(matrix + newside, matrix + columns*newside, newside, cols - newside);
	}
}

/*
	Transposes and swaps two given matrices. Params ROWS and COLS refer to the matrixA, i.e. the upper-right submatrix.
*/
template <class T> void MatrixTransposer::TransposeAndSwap(T* matrixA, T* matrixB, int rows, int cols)
{
	// rows and cols refer to MATRIX A (e.g. rows are cols of matrixB and vice versa)
	if (rows <= trivialBound && cols <= trivialBound)
	{
		TransposeAndSwapTrivially(matrixA, matrixB, rows, cols);
	}
	else
	{
		// submatrices
		int newrows = (rows / 2);
		int newcols = (cols / 2);

		// transpose and swap them
		TransposeAndSwap(matrixA, matrixB, newrows, newcols);
		TransposeAndSwap(matrixA + newcols, matrixB + columns*newcols, newrows, cols - newcols);
		TransposeAndSwap(matrixA + columns*newrows, matrixB + newrows, rows - newrows, newcols);
		TransposeAndSwap(matrixA + columns*newrows + newcols, matrixB + columns*newcols + newrows, rows - newrows, cols - newcols);
	}
}

/*
	Transposes and swaps all elements from one matrix for another matrixA[i][j] = matrixB[j][i].Params ROWS and COLS refer to the matrixA, i.e. the upper-right submatrix. 
*/
template <class T> void MatrixTransposer::TransposeAndSwapTrivially(T * matrixA, T * matrixB, int rows, int col)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			// copy = matrixA[i][j]
			T copy = *(matrixA + i * columns + j);
			// matrixA[i][j] = matrixB[j][i]
			*(matrixA + i * columns + j) = *(matrixB + j * columns + i);
			// matrixB[j][i] = copy
			*(matrixB + j * columns + i) = copy;
		}
	}
}

/*
	Transposes given matrix trivially.
*/
template <class T> void MatrixTransposer::TransposeTrivially(T * matrix, int rows, int col)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = i + 1; j < col; j++)
		{
			// copy = matrixA[i][j]
			T copy = *(matrix + i * columns + j);
			// matrixA[i][j] = matrixB[j][i]
			*(matrix + i * columns + j) = *(matrix + j * columns + i);
			// matrixB[j][i] = copy
			*(matrix + j * columns + i) = copy;
		}
	}
}
#pragma endregion

