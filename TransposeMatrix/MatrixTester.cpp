#include "MatrixTester.h"
#include "Transposition.h"
#include <ctime>
#include <chrono>

IntMatrixTester::IntMatrixTester(int lowerBoundSize)
{
	this->minSize = lowerBoundSize;
}

void IntMatrixTester::fillMatrix(int * matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		matrix[i] = i;
	}
}

double IntMatrixTester::testMatrixTrivially(int * matrix, int side, int iterations)
{
	long long totalTime = 0;
	fillMatrix(matrix, side*side);
	auto transposer = MatrixTransposer(side);
	transposer.trivialBound = minSize;
	for (int i = 0; i < iterations; i++)
	{
		const auto begin = std::chrono::steady_clock::now();
		transposer.TransposeOnDiagonalTrivially(matrix, side);
		const auto end = std::chrono::steady_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		totalTime += duration;
	}
	double meanTime = totalTime * 1.0 / iterations;
	return meanTime / ((side*side - side) / 2.0);
}

double IntMatrixTester::testMatrixCacheOblivious(int * matrix, int side, int iterations)
{
	long long totalTime = 0;
	fillMatrix(matrix, side*side);
	auto transposer = MatrixTransposer(side);
	transposer.trivialBound = minSize;
	for (int i = 0; i < iterations; i++)
	{
		const auto begin = std::chrono::steady_clock::now();
		transposer.TransposeOnDiagonal(matrix, side);
		const auto end = std::chrono::steady_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		totalTime += duration;
	}
	double meanTime = totalTime * 1.0 / iterations;
	return meanTime/ ((side*side - side)/2.0);
}
