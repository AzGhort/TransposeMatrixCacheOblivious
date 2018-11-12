#include <iostream>
#include "TransposeMatrix.h"

void fillMatrix(int* matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		matrix[i] = i;
	}
}

void testMatrix(int * matrix, int size)
{
	fillMatrix(matrix, size*size);
	MatrixWriter writer = MatrixWriter(size);
	writer.WriteMatrix<int>(matrix);
	MatrixTransposer transposer = MatrixTransposer(size);
	transposer.TransposeOnDiagonal<int>(matrix, size);
	writer.WriteMatrix(matrix);
}

int main()
{
	int matrix[25];
	testMatrix(matrix, 5);
}

