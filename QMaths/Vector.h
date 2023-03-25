#pragma once
#include <cstdarg>

#include "Matrix.h"

namespace QM
{
	class Quaternion;

	template <int size, typename scalar = float>
	class vector : public matrix<size, 1, scalar>
	{
	public:

		constexpr static std::size_t SIZE = size;
		using value_type = scalar;

		vector() 
		{
			for (int i = 1; i <= size; i++)
			{
				set(i, (scalar)0);
			}
		};

		template<typename... argTs>
		explicit vector(argTs... args) noexcept
		{
			static_assert(!(sizeof...(args) > size), "too many arguments for constructor");
			static_assert(!(sizeof...(args) < size), "too few arguments for constructor");
			
			std::size_t i{};

			((this->data[i++] = args), ...);
			
		};

		vector(matrix<size, 1, scalar> M);

		scalar get(int index);
		void set(int index, scalar value);

		void operator=(matrix<size, 1, scalar> M);

		scalar operator*(vector<size, scalar>& V);

		scalar magnitude();

		vector<size, scalar> normalise();

		vector<size, scalar> cross(vector<size, scalar>& V);

		scalar angle(vector<size, scalar>& V);

		vector<3, float> rotate(QM::Quaternion& Q);
	};

	template<int size, typename scalar>
	inline vector<size, scalar>::vector(matrix<size, 1, scalar> M)
	{
		for (int i = 1; i <= size; i++)
			this->set(i, M.get(i, 1));
	}

	template<int size, typename scalar>
	inline scalar vector<size, scalar>::get(int index)
	{
		return matrix<size, 1, scalar>::get(index, 1);
		
	}

	template<int size, typename scalar>
	inline void vector<size, scalar>::set(int index, scalar value)
	{
		matrix<size, 1, scalar>::set(index, 1, value);
	}

	template<int size, typename scalar>
	inline void vector<size, scalar>::operator=(matrix<size, 1, scalar> M)
	{
		for (int i = 1; i <= size; i++)
		{
			this->set(i, M.get(i, 1));
		}
	}

	template<int size, typename scalar>
	inline scalar vector<size, scalar>::operator*(vector<size, scalar>& V)
	{
		return (this->transpose() * V).get(1, 1);
	}

	template<int size, typename scalar>
	inline scalar vector<size, scalar>::magnitude()
	{
		scalar sum = 0;
		for (int i = 1; i <= size; i++)
		{
			sum += (get(i) * get(i));
		}
		return sqrt(sum);
	}

	template<int size, typename scalar>
	inline vector<size, scalar> vector<size, scalar>::normalise()
	{
		if (magnitude() == 0)
			return *this;

		vector<size, scalar> result = *this;
		for (int i = 1; i <= size; i++)
		{
			result.set(i, result.get(i) / magnitude());
		}
		return result;
	}

	template<int size, typename scalar>
	inline vector<size, scalar> vector<size, scalar>::cross(vector<size, scalar>& V)
	{
		static_assert(size == 3, "The cross product requires vectors with three elements");

		vector<3, scalar> result;
		result.set(1, this->get(2) * V.get(3) - this->get(3) * V.get(2));
		result.set(2, this->get(3) * V.get(1) - this->get(1) * V.get(3));
		result.set(3, this->get(1) * V.get(2) - this->get(2) * V.get(1));

		return result;
	}

	template<int size, typename scalar>
	inline scalar vector<size, scalar>::angle(vector<size, scalar>& V)
	{
		return deg(acos(((*this) * V) / (magnitude() * V.magnitude())));

	}

	template<typename scalar>
	inline vector<3, scalar> cross(vector<3, scalar>& V1, vector<3, scalar>& V2)
	{
		vector<3, scalar> result;
		result.set(1, V1.get(2) * V2.get(3) - V1.get(3) * V2.get(2));
		result.set(2, V1.get(3) * V2.get(1) - V1.get(1) * V2.get(3));
		result.set(1, V1.get(1) * V2.get(2) - V1.get(2) * V2.get(1));

		return result;
	}

	template<int size, typename scalar>
	inline scalar dist(vector<size, scalar>& v1, vector<size, scalar>& v2)
	{
		static_cast<vector<size, scalar>>(v1 - v2).magnitude();
	}

	template<int size, typename scalar>
	inline scalar dist(vector<size, scalar> v1, vector<size, scalar> v2)
	{
		return static_cast<vector<size, scalar>>(v1 - v2).magnitude();
	}
}