#pragma once
#include "Vector.h"

namespace QM
{
	struct eulerAngles
	{
		double xAngle, yAngle, zAngle;
	};

	class Quaternion
	{
	public:
		double r, x, y, z;

		Quaternion();
		Quaternion(double r, double x, double y, double z);
		Quaternion(double x, double y, double z);
		Quaternion(vector<3> vector);

		Quaternion(const Quaternion& q);
		void operator=(const Quaternion& q);

		Quaternion operator+(Quaternion q);
		void operator+=(Quaternion q);
		Quaternion operator-(Quaternion q);
		void operator-=(Quaternion q);
		Quaternion operator*(Quaternion q);
		void operator*=(Quaternion q);
		Quaternion operator/(Quaternion q);
		void operator/=(Quaternion q);

		Quaternion operator/(double d);
		void operator/=(double d);

		Quaternion inverse();
		Quaternion conjugate();
		Quaternion normalise();
		double magnitude();

		void rotate(Quaternion rotation);
		void translate(Quaternion translation);

		eulerAngles getEulerAngles();
	};

	Quaternion operator*(double d, Quaternion q);

	//angle in degrees
	//axis must have s=0
	Quaternion rotation(float angle, vector<3> axis);

	Quaternion rotation(double xAngle, double yAngle, double zAngle);

	template<int size, typename scalar>
	inline vector<3, float> vector<size, scalar>::rotate(QM::Quaternion& Q)
	{
		Quaternion Q1(*this);
		Q1.rotate(Q);

		return vector<3, float>(Q1.x, Q1.y, Q1.z);
	}

}