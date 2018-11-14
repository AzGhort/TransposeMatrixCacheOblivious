#include <iostream>
#include "TransposeMatrix.h"
#include "MatrixTester.h"
#include <iostream>
#include <fstream>
#include <string>
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

void generate_transposed_tuples(int* matrix, IntMatrixTester tester)
{

}

int main()
{
	int* matrix = new int[2] {0, 1};
	IntMatrixTester tester = IntMatrixTester(2);
	test_real_transposition_speed(matrix, tester);
}

