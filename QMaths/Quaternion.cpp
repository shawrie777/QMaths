#include "Quaternion.h"

#define _USE_MATH_DEFINES

#include "Quaternion.h"
#include <math.h>

namespace QM
{

	Quaternion::Quaternion() :r(0), x(0), y(0), z(0)
	{
	}

	Quaternion::Quaternion(double r, double x, double y, double z) : r(r), x(x), y(y), z(z)
	{
	}

	Quaternion::Quaternion(double x, double y, double z) : r(0), x(x), y(y), z(z)
	{
	}

	Quaternion::Quaternion(vector<3> v) : r(0), x(v.get(1)), y(v.get(2)), z(v.get(3))
	{
	}

	Quaternion::Quaternion(const Quaternion& q) : r(q.r), x(q.x), y(q.y), z(q.z)
	{
	}


	void Quaternion::operator=(const Quaternion& q)
	{
		this->r = q.r;
		this->x = q.x;
		this->y = q.y;
		this->z = q.z;
	}


	Quaternion Quaternion::operator+(Quaternion q)
	{
		return Quaternion(this->r + q.r, this->x + q.x, this->y + q.y, this->z + q.z);
	}

	void Quaternion::operator+=(Quaternion q)
	{
		this->r += q.r;
		this->x += q.x;
		this->y += q.y;
		this->z += q.z;
	}

	Quaternion Quaternion::operator-(Quaternion q)
	{
		return Quaternion(this->r - q.r, this->x - q.x, this->y - q.y, this->z - q.z);
	}

	void Quaternion::operator-=(Quaternion q)
	{
		this->r -= q.r;
		this->x -= q.x;
		this->y -= q.y;
		this->z -= q.z;
	}

	Quaternion Quaternion::operator*(Quaternion q)
	{
		Quaternion result;
		result.r = this->r * q.r - q.x * this->x - this->y * q.y - this->z * q.z;
		result.x = this->r * q.x + q.r * this->x + this->y * q.z - this->z * q.y;
		result.y = this->r * q.y + q.r * this->y + this->z * q.x - this->x * q.z;
		result.z = this->r * q.z + q.r * this->z + this->x * q.y - this->y * q.x;
		return result;
	}

	void Quaternion::operator*=(Quaternion q)
	{
		*this = *this * q;
	}

	Quaternion Quaternion::operator/(Quaternion q)
	{
		return q * this->inverse();
	}

	void Quaternion::operator/=(Quaternion q)
	{
		*this = *this / q;
	}

	Quaternion Quaternion::operator/(double d)
	{
		return Quaternion(r / d, x / d, y / d, z / d);
	}

	void Quaternion::operator/=(double d)
	{
		*this = *this / d;
	}

	Quaternion Quaternion::inverse()
	{
		return (1 / (magnitude() * magnitude())) * conjugate();
	}

	Quaternion Quaternion::conjugate()
	{
		return Quaternion(r, -x, -y, -z);
	}

	Quaternion Quaternion::normalise()
	{
		return *this / magnitude();
	}

	double Quaternion::magnitude()
	{
		return sqrt(r * r + x * x + y * y + z * z);
	}

	void Quaternion::rotate(Quaternion rotation)
	{
		*this = rotation * *this * rotation.inverse();
	}

	void Quaternion::translate(Quaternion translation)
	{
		this->x += translation.x;
		this->y += translation.y;
		this->z += translation.z;
	}

	eulerAngles Quaternion::getEulerAngles()
	{
		eulerAngles angles;
		double numerator, denominator;

		numerator = 2 * (r * x + y * z);
		denominator = 1 - 2 * (x * x + y * y);

		if (numerator == 0 && denominator == 0)
			angles.xAngle = 0;
		else
			angles.xAngle = atan2(numerator, denominator);
		
		double pitchTemp = 2 * (r * y + z * x);
		angles.yAngle = std::abs(pitchTemp) >= 1 ? std::copysign(M_PI / 2, pitchTemp) : std::asin(pitchTemp);

		numerator = 2 * (r * z + x * y);
		denominator = 1 - 2 * (y * y + z * z);

		if (numerator == 0 && denominator == 0)
			angles.zAngle = 0;
		else
			angles.zAngle = atan2(numerator, denominator);
		return angles;
	}

	Quaternion operator*(double d, Quaternion q)
	{
		return Quaternion(d * q.r, d * q.x, d * q.y, d * q.z);
	}

	Quaternion rotation(float angle, vector<3> axis)
	{
		if (axis.get(1) == 0 && axis.get(2) == 0 && axis.get(3) == 0)
			return Quaternion(1, 0, 0, 0);
		else
		{
			Quaternion unitAxis = axis.normalise();
			double radAngle = (angle * M_PI / 180) / 2;

			return Quaternion(cos(radAngle), unitAxis.x * sin(radAngle), unitAxis.y * sin(radAngle), unitAxis.z * sin(radAngle));
		}
	}

	Quaternion rotation(double xAngle, double yAngle, double zAngle)
	{
		double cosX = cos(rad(xAngle) / 2);
		double sinX = sin(rad(xAngle) / 2);
		double cosY = cos(rad(yAngle) / 2);
		double sinY = sin(rad(yAngle) / 2);
		double cosZ = cos(rad(zAngle) / 2);
		double sinZ = sin(rad(zAngle) / 2);

		double r = cosX * cosY * cosZ + sinX * sinY * sinZ;
		double x = sinX * cosY * cosZ - cosX * sinY * sinZ;
		double y = cosX * sinY * cosZ + sinX * cosY * sinZ;
		double z = cosX * cosY * sinZ - sinX * sinY * cosZ;

		return Quaternion(r, x, y, z);
	}

}