#pragma once

#include "Core.h"

#pragma warning(push)
#pragma warning(disable: 26451)

namespace QM
{
	template <int rows, int cols, typename scalar = float>
	class matrix
	{
	protected:
		int m_rows, m_cols;
		std::vector<scalar> data;
	public:
		matrix();

		const scalar* pointer() const;

		scalar get(int row, int col) const;
		void set(int row, int col, scalar value);

		matrix<cols, rows, scalar> transpose() const;

		matrix<rows, cols, scalar> operator+(const matrix<rows, cols, scalar>& m) const;
		void operator+=(const matrix<rows, cols, scalar>& m);
		
		matrix<rows, cols, scalar> operator-(const matrix<rows, cols, scalar>& m) const;
		void operator-=(const matrix<rows, cols, scalar>& m);

		template <int cols2>
		matrix<rows, cols2, scalar> operator*(const matrix<cols, cols2, scalar>& m) const;

		matrix<rows, cols, scalar> Hadamard(const matrix<rows, cols, scalar>& m) const;


		bool operator==(const matrix<rows, cols, scalar>& m)const;
		bool operator!=(const matrix<rows, cols, scalar>& m)const;
	};

	template<int rows, int cols, typename scalar>
	inline matrix<rows, cols, scalar>::matrix()
	{
		m_rows = rows;
		m_cols = cols;
		data.resize(m_rows * m_cols);
	}

	template<int rows, int cols, typename scalar>
	const inline scalar* matrix<rows, cols, scalar>::pointer() const
	{
		return data.data();
	}

	template<int rows, int cols, typename scalar>
	inline scalar matrix<rows, cols, scalar>::get(int row, int col) const
	{
		return data[(row - 1) * m_cols + col - 1];
	}

	template<int rows, int cols, typename scalar>
	inline void QM::matrix<rows, cols, scalar>::set(int row, int col, scalar value)
	{
		try {
			data.at((row - 1) * m_cols + col - 1) = value;
		}
		catch (std::out_of_range& error)
		{
			std::cerr << "There is no element at (" << row << "," << col << ") to change." << error.what() << std::endl;
		}
	}

	template<int rows, int cols, typename scalar>
	inline matrix<cols,rows,scalar> matrix<rows, cols, scalar>::transpose() const
	{
		matrix<cols, rows, scalar> result;
		
		for (int r = 0; r < m_rows; r++)
		{
			for (int c = 0; c < m_cols; c++)
			{
				result.set(c + 1, r + 1, get(r + 1, c + 1));
			}
		}

		return result;
	}

	template<int rows, int cols, typename scalar>
	inline matrix<rows, cols, scalar> matrix<rows, cols, scalar>::operator+(const matrix<rows, cols, scalar>& m) const
	{
		if (m.m_cols != m_cols && m.m_rows != m_rows)
		{
			throw ("These matrices are incompatible for addition.");
		}

		matrix<rows, cols, scalar> result;
		for (int i = 0; i < result.data.size(); i++)
		{
			result.data[i] = data[i] + m.data[i];
		}

		return result;
	}

	template<int rows, int cols, typename scalar>
	inline void QM::matrix<rows, cols, scalar>::operator+=(const matrix<rows, cols, scalar>& m)
	{
		if (m.m_cols != m_cols && m.m_rows != m_rows)
		{
			throw ("These matrices are incompatible for addition.");
		}

		for (int i = 0; i < data.size(); i++)
		{
			data[i] += m.data[i];
		}
	}

	template<int rows, int cols, typename scalar>
	inline matrix<rows, cols, scalar> matrix<rows, cols, scalar>::operator-(const matrix<rows, cols, scalar>& m) const
	{
		if (m.m_cols != m_cols && m.m_rows != m_rows)
		{
			throw ("These matrices are incompatible for subtraction.");
		}

		matrix<rows, cols, scalar> result;
		for (int i = 0; i < result.data.size(); i++)
		{
			result.data[i] = data[i] - m.data[i];
		}

		return result;
	}

	template<int rows, int cols, typename scalar>
	inline void QM::matrix<rows, cols, scalar>::operator-=(const matrix<rows, cols, scalar>& m)
	{
		if (m.m_cols != m_cols && m.m_rows != m_rows)
		{
			throw ("These matrices are incompatible for subtraction.");
		}

		for (int i = 0; i < data.size(); i++)
		{
			data[i] -= m.data[i];
		}
	}

	template<int rows, int cols, typename scalar>
	inline matrix<rows, cols, scalar> matrix<rows, cols, scalar>::Hadamard(const matrix<rows, cols, scalar>& m) const
	{
		matrix<rows, cols, scalar> result;
		
		for (int i = 0; i < data.size(); i++)
			result.data[i] = m.data[i] * this->data[i];

		return result;
	}

	template<int rows, int cols, typename scalar>
	inline bool matrix<rows, cols, scalar>::operator==(const matrix<rows, cols, scalar>& m) const
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i] != m.data[i])
				return false;
		}
		return true;
	}

	template<int rows, int cols, typename scalar>
	inline bool matrix<rows, cols, scalar>::operator!=(const matrix<rows, cols, scalar>& m) const
	{
		return !(*this == m);
	}

	template<int rows, int cols, typename scalar>
	inline matrix<rows, cols, scalar> operator*(float f, matrix<rows, cols, scalar> m)
	{
		matrix<rows, cols, scalar> result;

		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= cols; j++)
			{
				result.set(i, j, f * m.get(i, j));
			}
		}

		return result;
	}


	template<int rows, int cols, typename scalar>
	template<int cols2>
	inline matrix<rows, cols2, scalar> matrix<rows, cols, scalar>::operator*(const matrix<cols, cols2, scalar>& m) const
	{
		matrix<rows, cols2, scalar> result;

		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= cols2; j++)
			{
				scalar total = 0;
				for (int k = 1; k <= cols; k++)
				{
					total += get(i, k) * m.get(k, j);
				}
				result.set(i, j, total);
			}
		}

		return result;
	}

}

template<int rows, int cols, typename scalar>
inline std::ostream& operator<<(std::ostream& os, QM::matrix<rows, cols, scalar> mat)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			os << mat.get(i + 1, j + 1) << ",  ";
		}
		os << std::endl;
	}

	return os;
}

//specialisation for square matrices
namespace QM
{
	template <int size, typename scalar>
	class matrix<size,size,scalar>
	{
	private:
		int m_size;
		std::vector<scalar> data;
	public:
		matrix();

		const scalar* pointer() const;

		scalar get(int row, int col) const;
		void set(int row, int col, scalar value);

		matrix<size, size, scalar> transpose() const;

		matrix<size, size, scalar> operator+(const matrix<size, size, scalar>& m) const;
		void operator+=(const matrix<size, size, scalar>& m);

		matrix<size, size, scalar> operator-(const matrix<size, size, scalar>& m) const;
		void operator-=(const matrix<size, size, scalar>& m);

		template <int cols2>
		matrix<size, cols2, scalar> operator*(const matrix<size, cols2, scalar>& m) const;

		matrix<size, size, scalar> Hadamard(const matrix<size, size, scalar>& m) const;

		scalar trace() const;

		std::pair<matrix<size, size, scalar>, matrix<size, size, scalar>> LU_decomposition() const;

		scalar det() const;

		matrix<size, size, float>inverse() const;

		bool operator!=(const matrix<size, size, scalar>& m)const;
		bool operator==(const matrix<size, size, scalar>& m)const;
	};

	template <int size, typename scalar>
	inline matrix<size, size, scalar>::matrix()
	{
		m_size = size;		
		data.resize(m_size * m_size);
	}

	template <int size, typename scalar>
	const inline scalar* matrix<size, size, scalar>::pointer()  const
	{
		return (scalar*)(data.data());
	}

	template <int size, typename scalar>
	inline scalar matrix<size, size, scalar>::get(int row, int col) const
	{
		return data[(row - 1) * m_size + col - 1];
	}

	template <int size, typename scalar>
	inline void QM::matrix<size, size, scalar>::set(int row, int col, scalar value)
	{
		try {
			data.at((row - 1) * m_size + col - 1) = value;
		}
		catch (std::out_of_range& error)
		{
			std::cerr << "There is no element at (" << row << "," << col << ") to change." << error.what() << std::endl;
		}
	}

	template<int size, typename scalar>
	inline matrix<size, size, scalar> matrix<size, size, scalar>::transpose() const
	{
		matrix<size, size, scalar> result;

		for (int r = 0; r < m_size; r++)
		{
			for (int c = 0; c < m_size; c++)
			{
				result.set(c + 1, r + 1, get(r + 1, c + 1));
			}
		}

		return result;
	}

	template<int size, typename scalar>
	inline matrix<size, size, scalar> matrix<size, size, scalar>::operator+(const matrix<size, size, scalar>& m) const
	{
		if (m.m_size != m_size)
		{
			throw ("These matrices are incompatible for addition.");
		}

		matrix<size, size, scalar> result;
		for (unsigned int i = 0; i < result.data.size(); i++)
		{
			result.data[i] = data[i] + m.data[i];
		}

		return result;
	}

	template<int size, typename scalar>
	inline void QM::matrix<size, size, scalar>::operator+=(const matrix<size, size, scalar>& m)
	{
		if (m.m_size != m_size)
		{
			throw ("These matrices are incompatible for addition.");
		}

		for (unsigned int i = 0; i < data.size(); i++)
		{
			data[i] += m.data[i];
		}
	}

	template<int size, typename scalar>
	inline matrix<size, size, scalar> matrix<size, size, scalar>::operator-(const matrix<size, size, scalar>& m) const
	{
		if (m.m_size != m_size)
		{
			throw ("These matrices are incompatible for subtraction.");
		}

		matrix<size, size, scalar> result;
		for (unsigned int i = 0; i < result.data.size(); i++)
		{
			result.data[i] = data[i] - m.data[i];
		}

		return result;
	}

	template<int size, typename scalar>
	inline void QM::matrix<size, size, scalar>::operator-=(const matrix<size, size, scalar>& m)
	{
		if (m.m_size != m_size)
		{
			throw ("These matrices are incompatible for subtraction.");
		}

		for (unsigned int i = 0; i < data.size(); i++)
		{
			data[i] -= m.data[i];
		}
	}

	template<int size, typename scalar>
	inline scalar matrix<size, size, scalar>::trace() const
	{
		scalar result = 0;
		for (int i = 1; i <= size; i++)
		{
			result += get(i, i);
		}
		return result;
	}

	template<int size, typename scalar>
	inline std::pair<matrix<size, size, scalar>, matrix<size, size, scalar>> matrix<size, size, scalar>::LU_decomposition() const
	{
		matrix<size, size, scalar> lower, upper;

		for (int i = 1; i <= size; i++)
		{
			//upper
			for (int k = i; k <= size; k++)
			{
				scalar sum = 0;
				for (int j = 1; j <= i; j++)
				{
					sum += (lower.get(i, j) * upper.get(j, k));
				}
				upper.set(i, k, get(i, k) - sum);
			}

			//lower
			for (int k = i; k <= size; k++)
			{
				if (i == k)
				{
					lower.set(i, i, 1);
				}
				else
				{
					scalar sum = 0;
					for (int j = 1; j <= i; j++)
					{
						sum += (lower.get(k, j) * upper.get(j, i));
					}
					lower.set(k, i, (get(k, i) - sum) / upper.get(i, i));
				}
			}
		}
		


		return std::pair<matrix<size, size, scalar>, matrix<size, size, scalar>>(lower,upper);
	}

	template<int size, typename scalar>
	inline scalar matrix<size, size, scalar>::det() const
	{
		std::pair<matrix<size, size, scalar>, matrix<size, size, scalar>> decomp = LU_decomposition();
		scalar det1 = 1;
		scalar det2 = 1;
		for (int i = 1; i <= size; i++)
		{
			det1 *= decomp.first.get(i, i);
			det2 *= decomp.second.get(i, i);
		}

		return det1 * det2;
	}

	template<int size, typename scalar>
	inline matrix<size, size, float> matrix<size, size, scalar>::inverse() const
	{
		if (det() == 0)
			throw("This matrix has no inverse");
		else
		{
			std::pair<matrix<size, size, scalar>, matrix<size, size, scalar>> decomp = LU_decomposition();
			matrix<size, size, scalar> L = decomp.first;
			matrix<size, size, scalar> U = decomp.second;
			
			matrix<size, size> L_inverse;

			for (unsigned int row = 1; row <= size; row++)
			{
				for (unsigned int col = 1; col <= row; col++)
				{
					if (col == row)
					{
						L_inverse.set(row, col, 1/L.get(row,col));
					}
					else
					{
						scalar sum = 0;
						for (unsigned int k = col; k < row; k++)
						{
							sum += L.get(row, k) * L_inverse.get(k, col);
						}
						L_inverse.set(row, col, -sum / L.get(row, row));
					}
				}
			}

			matrix<size, size, scalar> U_inverse;
			for (unsigned int row = size; row > 0; row--)
			{
				for (unsigned int col = size; col >= row; col--)
				{
					if (col == row)
					{
						U_inverse.set(row, col, 1 / U.get(row, col));
					}
					else
					{
						scalar sum = 0;
						for (int k = row; k <= size; k++)
						{
							sum += U.get(row, k) * U_inverse.get(k, col);
						}
						U_inverse.set(row, col, -sum / U.get(row, row));
					}
				}
			}

			return U_inverse * L_inverse;
		}


		return matrix<size, size, float>();
	}

	template<int size, typename scalar>
	template<int cols2>
	inline matrix<size, cols2, scalar> matrix<size, size, scalar>::operator*(const matrix<size, cols2, scalar>& m) const
	{
		matrix<size, cols2, scalar> result;

		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= cols2; j++)
			{
				scalar total = 0;
				for (int k = 1; k <= size; k++)
				{
					total += get(i, k) * m.get(k, j);
				}
				result.set(i, j, total);
			}
		}

		return result;
	}

	template<int size, typename scalar = float>
	inline matrix<size, size, scalar> identity()
	{
		matrix<size, size, scalar> result;
		for (int i = 1; i <= size; i++)
			result.set(i, i, 1);

		return result;
	}

	template<int size, typename scalar>
	inline matrix<size, size, scalar> matrix<size, size, scalar>::Hadamard(const matrix<size, size, scalar>& m) const
	{
		matrix<size, size, scalar> result;

		for (unsigned int i = 0; i < data.size(); i++)
			result.data[i] = m.data[i] * this->data[i];

		return result;
	}

	template<int size, typename scalar>
	inline bool matrix<size, size, scalar>::operator==(const matrix<size, size, scalar>& m) const
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i] != m.data[i])
				return false;
		}
		return true;
	}

	template<int size, typename scalar>
	inline bool matrix<size, size, scalar>::operator!=(const matrix<size, size, scalar>& m) const
	{
		return !(*this == m);
	}
}

template<int size, typename scalar>
inline std::ostream& operator<<(std::ostream& os, QM::matrix<size, size, scalar> mat)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			os << mat.get(i + 1, j + 1) << ",  ";
		}
		os << std::endl;
	}

	return os;
}