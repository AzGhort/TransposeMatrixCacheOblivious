#pragma once
/*
	Auxiliary class, used for writing contents of given matrix.
*/
class MatrixWriter
{
	public:
		MatrixWriter(int col);
		template <class T> void WriteMatrix(T *matrix);
		
	private:
		int columns;
};

/*
	Writes given matrix to standard output.
*/
template<class T> void MatrixWriter::WriteMatrix(T *matrix)
{
	std::cout << "Matrix:\n";
	for (int i = 0; i < (columns * columns); i++)
	{
		std::cout << matrix[i] << " ";
		if ((i + 1) % columns == 0)
		{
			std::cout << "\n";
		}
	}
	for (int i = 0; i < columns * 2; i++)	std::cout << "-";
	std::cout << "\n";
}
