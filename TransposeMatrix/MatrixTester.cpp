#include "MatrixTester.h"
#include "Transposition.h"
#include <ctime>
#include <chrono>

/*
	Fills matrix with numbers 0 to N^2 - 1.
*/
void IntMatrixTester::fillMatrix(int * matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		matrix[i] = i;
	}
}

/*
	Trivially transposes given matrix in given number of iterations, and returns average speed for swapping two elements.
*/
double IntMatrixTester::testMatrixTrivially(int * matrix, int side, int iterations)
{
	long long totalTime = 0;
	fillMatrix(matrix, side*side);
	auto transposer = MatrixTransposer(side);
	for (int i = 0; i < iterations; i++)
	{
		const auto begin = std::chrono::steady_clock::now();
		transposer.TransposeTrivially(matrix, side, side);
		const auto end = std::chrono::steady_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		totalTime += duration;
	}
	double meanTime = totalTime * 1.0 / iterations;
	return meanTime / ((side*side - side) / 2.0);
}

/*
	Cache obliviously transposes given matrix in given number of iterations, and returns average speed for swapping two elements.
*/
double IntMatrixTester::testMatrixCacheOblivious(int * matrix, int side, int iterations)
{
	long long totalTime = 0;
	fillMatrix(matrix, side*side);
	auto transposer = MatrixTransposer(side);
	for (int i = 0; i < iterations; i++)
	{
		const auto begin = std::chrono::steady_clock::now();
		transposer.Transpose(matrix, side, side);
		const auto end = std::chrono::steady_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		totalTime += duration;
	}
	double meanTime = totalTime * 1.0 / iterations;
	return meanTime/ ((side*side - side)/2.0);
}
