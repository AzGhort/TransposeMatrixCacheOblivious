#pragma once
class MatrixWriter
{
	public:
		MatrixWriter(int col);
		template <class T> void WriteMatrix(T *matrix);

	private:
		int columns;
};

template<class T>
inline void MatrixWriter::WriteMatrix(T *matrix)
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
