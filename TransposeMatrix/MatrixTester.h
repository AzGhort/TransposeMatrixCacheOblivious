#pragma once
/*
	Tester class, used for testing of matrix transposition.
*/
class IntMatrixTester
{
	public:
		double testMatrixTrivially(int* matrix, int size, int iterations);
		double testMatrixCacheOblivious(int* matrix, int size, int iterations);

	private: 
		void fillMatrix(int* matrix, int size);
};