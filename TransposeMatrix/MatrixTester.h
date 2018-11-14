#pragma once
class IntMatrixTester
{
	public:
		IntMatrixTester(int lowerBoundSize);
		double testMatrixTrivially(int* matrix, int size, int iterations);
		double testMatrixCacheOblivious(int* matrix, int size, int iterations);

	private: 
		int minSize;
		void fillMatrix(int* matrix, int size);
};