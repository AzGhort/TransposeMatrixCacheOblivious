#include "Transposition.h"

MatrixTransposer::MatrixTransposer(int cols)
{
	columns = cols;
}

#pragma region Transposed elements indices generating

/*
	Simulates transposition of matrix of given dimension, either trivially or recursively.
	All procedures below are equivalent to corresponding functions in Transposition.h except that they write swapped elements to standard output.
*/
void MatrixTransposer::SimulateTransposition(int side, bool trivial)
{
	std::cout << "N " << side << "\n";
	if (trivial) GenerateTransposedElementsTrivially(0, 0, side);
	else GenerateTransposedElements(0, 0, side);
	std::cout << "E" << "\n";
}

void MatrixTransposer::GenerateTransposedElements(int row, int column, int side)
{
	// only square matrices in diagonal transposition
	if (side <= trivialBound)
	{
		GenerateTransposedElementsTrivially(row, column, side);
	}
	else
	{
		int newside = (side / 2);
		// transpose
		GenerateTransposedElements(row, column, newside);
		GenerateTransposedElements(row + newside, column + newside, side - newside);
		GenerateTransposedElementsAndSwap(row, column + newside, row + newside, column, newside, side - newside);
	}
}

void MatrixTransposer::GenerateTransposedElementsAndSwap(int rowA, int columnA, int rowB, int columnB, int rows, int cols)
{
	if (rows <= trivialBound && cols <= trivialBound)
	{
		GenerateTransposedElementsAndSwapTrivially(rowA, columnA, rowB, columnB, rows, cols);
	}
	else
	{
		// submatrices
		int newrows = (rows / 2);
		int newcols = (cols / 2);

		// transpose and swap them
		GenerateTransposedElementsAndSwap(rowA, columnA, rowB, columnB, newrows, newcols);
		GenerateTransposedElementsAndSwap(rowA, columnA + newcols, rowB  + newcols, columnB, newrows, cols - newcols);
		GenerateTransposedElementsAndSwap(rowA + newrows, columnA, rowB, columnB + newrows, rows - newrows, newcols);
		GenerateTransposedElementsAndSwap(rowA + newrows, columnA + newcols, rowB + newcols, columnB + newrows, rows - newrows, cols - newcols);
	}
}

void MatrixTransposer::GenerateTransposedElementsAndSwapTrivially(int rowA, int columnA, int rowB, int columnB, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << "X " << (rowA + i) << " " << (columnA + j) << " " << (rowB + j) << " " << (columnB + i) << "\n";
		}
	}
}

void MatrixTransposer::GenerateTransposedElementsTrivially(int row, int column, int side)
{
	for (int i = 0; i < side; i++)
	{
		for (int j = i + 1; j < side; j++)
		{
			std::cout << "X " << (row + i) << " " << (column + j) << " " << (row + j) << " " << (column + i) << "\n";
		}
	}
}
#pragma endregion
