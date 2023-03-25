#pragma once

#include "Matrix.h"

namespace QM
{
	template <int size>
	class translation : public matrix<size, size, float>
	{
	};

	template <>
	class translation<3> : public matrix<3, 3, float>
	{
	public:
		translation(float x, float y);
		translation(vector<2> v);
	};

	template <>
	class translation<4> : public matrix<4, 4, float>
	{
	public:
		translation(float x, float y, float z);
		translation(vector<3> v);
	};


	inline translation<3>::translation(float x, float y)
	{
		this->set(1, 1, 1);
		this->set(2, 2, 1);
		this->set(3, 3, 1);
		this->set(1, 3, x);
		this->set(2, 3, y);
	}

	inline translation<3>::translation(vector<2> v)
	{
		this->set(1, 1, 1);
		this->set(2, 2, 1);
		this->set(3, 3, 1);
		this->set(1, 3, v.get(1));
		this->set(2, 3, v.get(2));
	}

	inline translation<4>::translation(float x, float y, float z)
	{
		this->set(1, 1, 1);
		this->set(2, 2, 1);
		this->set(3, 3, 1);
		this->set(4, 4, 1);
		this->set(1, 4, x);
		this->set(2, 4, y);
		this->set(3, 4, z);
	}

	inline translation<4>::translation(vector<3> v)
	{
		this->set(1, 1, 1);
		this->set(2, 2, 1);
		this->set(3, 3, 1);
		this->set(4, 4, 1);
		this->set(1, 4, v.get(1));
		this->set(2, 4, v.get(2));
		this->set(3, 4, v.get(3));
	}


	template <int size>
	class scale : public matrix<size, size, float>
	{
	};

	template <>
	class scale<3> : public matrix<3, 3, float>
	{
	public:
		scale(float x, float y);
	};

	template <>
	class scale<4> : public matrix<4, 4, float>
	{
	public:
		scale(float x, float y, float z);
	};

	inline scale<3>::scale(float x, float y)
	{
		this->set(1, 1, x);
		this->set(2, 2, y);
		this->set(3, 3, 1);
	}
	inline scale<4>::scale(float x, float y, float z)
	{
		this->set(1, 1, x);
		this->set(2, 2, y);
		this->set(3, 3, z);
		this->set(4, 4, 1);
	}

	template<int size>
	class Mrotation : public matrix<size, size, float>
	{
	};

	template<>
	class Mrotation<3> : public matrix<3, 3, float>
	{
	public:
		Mrotation(float angle);
	};

	template<>
	class Mrotation<4> : public matrix<4, 4, float>
	{
	public:
		Mrotation(float angle, vector<3,float> axis);
	};

	inline Mrotation<3>::Mrotation(float angle)
	{
		this->set(1, 1, (float)cos(rad(angle)));
		this->set(1, 2, -(float)sin(rad(angle)));
		this->set(2, 1, (float)sin(rad(angle)));
		this->set(2, 2, (float)cos(rad(angle)));
		this->set(3, 3, 1.0f);
	}

	inline Mrotation<4>::Mrotation(float angle, vector<3, float> axis)
	{
		float C = (float)cos(rad(angle));
		float S = (float)sin(rad(angle));
		vector<3, float> U = axis.normalise();

		this->set(1, 1, C + U.get(1) * U.get(1) * (1 - C));
		this->set(1, 2, U.get(1) * U.get(2) * (1 - C) - U.get(3) * S);
		this->set(1, 3, U.get(1) * U.get(3) * (1 - C) + U.get(2) * S);
		this->set(1, 4, 0);

		this->set(2, 1, U.get(2) * U.get(1) * (1 - C) + U.get(3) * S);
		this->set(2, 2, C + U.get(2) * U.get(2) * (1 - C));
		this->set(2, 3, U.get(2) * U.get(3) * (1 - C) - U.get(1) * S);
		this->set(2, 4, 0);

		this->set(3, 1, U.get(3) * U.get(1) * (1 - C) - U.get(2) * S);
		this->set(3, 2, U.get(3) * U.get(2) * (1 - C) + U.get(1) * S);
		this->set(3, 3, C + U.get(3) * U.get(3) * (1 - C));
		this->set(3, 4, 0);

		this->set(4, 1, 0);
		this->set(4, 2, 0);
		this->set(4, 3, 0);
		this->set(4, 4, 1);
	}
}