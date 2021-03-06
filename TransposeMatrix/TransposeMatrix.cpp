#include <iostream>
#include "TransposeMatrix.h"
#include "MatrixTester.h"
#include <iostream>
#include <fstream>
#include <string>

/*
	Tests speed of transposition for matrices of size N = ⌈2k/9⌉ for K=54, 55, ... in an endless loop.
	For each matrix size, outputs speed of trivial and CO transpose to file named "matrixK.txt", and also to standard out.
*/
void test_real_transposition_speed(int* matrix, IntMatrixTester tester)
{
	int k = 54;
	while (true)
	{
		int N = ceil(pow(2.0, k / 9.0));
		matrix = new int[N*N];
		double time1 = tester.testMatrixTrivially(matrix, N, 5);
		double time2 = tester.testMatrixCacheOblivious(matrix, N, 5);
		std::ofstream file;
		file.open("matrix" + std::to_string(k) + ".txt");
		file << N << " " << time1 << " " << time2 << "\n";
		std::cout << "Matrix (N = " << N << ") ----- trivial: " << time1 << ", cache-oblivous: " << time2 << "\n";
		file.close();
		delete(matrix);
		k++;
	}
}

/*
	Generates swapped elements tuples for matrices of size N = ⌈2k/9⌉ for K=54, 55, ... in an endless loop.
	For each matrix, outputs (both for trivial and CO) to standard out:
	N N
	X i1 j1 i2 j2 (for each element]
	E
*/
void generate_transposed_tuples()
{
	int k = 54;
	while (true)
	{
		if (k == 123) break;
		int N = ceil(pow(2.0, k / 9.0));
		MatrixTransposer transposer = MatrixTransposer(N);
		transposer.SimulateTransposition(N, true);
		transposer.SimulateTransposition(N, false);
		k++;
	}
}

int main()
{
	int* matrix = new int[2] {0, 1};
	IntMatrixTester tester = IntMatrixTester();
	test_real_transposition_speed(matrix, tester);
	
	// uncomment this to generate transposed elements
	//generate_transposed_tuples();
}

