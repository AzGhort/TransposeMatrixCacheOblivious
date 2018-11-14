#pragma once
class MatrixTransposer
{
	public:
		MatrixTransposer(int cols);
		template <class T> void TransposeOnDiagonal(T* matrix, int side);
		template <class T> void TransposeAndSwap(T* matrixA, T* matrixB, int side);
		template <class T> void TransposeEdge(T* column, T* row, int side);
		template <class T> void TransposeAndSwapTrivially(T* matrixA, T* matrixB, int side);
		template <class T> void TransposeOnDiagonalTrivially(T* matrix, int side);
		int trivialBound = 10;
	private:
		int columns;
};

template <class T> void MatrixTransposer::TransposeOnDiagonal(T* matrix, int side)
{
	// nothing to transpose
	if (side <= trivialBound)
	{
		TransposeOnDiagonalTrivially(matrix, side);
	}
	else
	{
		// submatrices
		int newside = (side / 2);
		T* matrix11 = matrix;
		T* matrix12 = matrix11 + newside;
		T* matrix21 = matrix11 + columns * newside;
		T* matrix22 = matrix21 + newside;

		// transpose
		TransposeOnDiagonal(matrix11, newside);
		TransposeOnDiagonal(matrix22, newside);
		TransposeAndSwap(matrix12, matrix21, newside);

		// not the ideal case :( 
		// swap the last column for last row
		if (side % 2 == 1)
		{
			T* lastColumn = matrix + side - 1;
			T* lastRow = matrix + columns * (side - 1);
			TransposeEdge(lastColumn, lastRow, side - 1);
		}
	}
}

template <class T> void MatrixTransposer::TransposeAndSwap(T* matrixA, T* matrixB, int side)
{
	if (side <= trivialBound)
	// just swap whatever the pointers are pointing to 
	{
		TransposeAndSwapTrivially(matrixA, matrixB, side);
	}
	else
	{
		// submatrices
		int newside = (side / 2);
		T* matrixA11 = matrixA;
		T* matrixA12 = matrixA11 + newside;
		T* matrixA21 = matrixA11 + columns * newside;
		T* matrixA22 = matrixA21 + newside;
		T* matrixB11 = matrixB;
		T* matrixB12 = matrixB11 + newside;
		T* matrixB21 = matrixB11 + columns * newside;
		T* matrixB22 = matrixB21 + newside;

		// transpose and swap them
		TransposeAndSwap(matrixA11, matrixB11, newside);
		TransposeAndSwap(matrixA12, matrixB21, newside);
		TransposeAndSwap(matrixA21, matrixB12, newside);
		TransposeAndSwap(matrixA22, matrixB22, newside);

		// not the ideal case :( 
		// swap the last column for last row
		if (side % 2 == 1)
		{
			T* lastColumnA = matrixA + side - 1;
			T* lastRowA = matrixA + columns * (side - 1);
			T* lastColumnB = matrixB + side - 1;
			T* lastRowB = matrixB + columns * (side - 1);
			TransposeEdge(lastColumnA, lastRowB, side);
			TransposeEdge(lastColumnB, lastRowA, side - 1);
		}
	}
}

template <class T> void MatrixTransposer::TransposeEdge(T * column, T * row, int side)
{
	T * colPtr = column;
	T * rowPtr = row;

	for (int i = 0; i < side; i++)
	{
		TransposeAndSwapTrivially(colPtr, rowPtr, 1);
		rowPtr++;
		colPtr += columns;
	}
}

template<class T> void MatrixTransposer::TransposeAndSwapTrivially(T * matrixA, T * matrixB, int side)
{
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			// copy = matrixA[i][j]
			T copy = *(matrixA + i * side + j);
			// matrixA[i][j] = matrixB[j][i]
			*(matrixA + i * side + j) = *(matrixB + j * side + i);
			// matrixB[j][i] = copy
			*(matrixB + j * side + i) = copy;
		}
	}
}

template<class T> void MatrixTransposer::TransposeOnDiagonalTrivially(T * matrix, int side)
{
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			if (j > i)
			{
				// copy = matrix[i][j]
				T copy = *(matrix + i * side + j);
				// matrix[i][j] = matrix[j][i]
				*(matrix + i * side + j) = *(matrix + j * side + i);
				// matrix[j][i] = copy
				*(matrix + j * side + i) = copy;
			}
		}
	}
}
