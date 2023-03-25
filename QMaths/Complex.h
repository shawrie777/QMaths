#pragma once

#include "Core.h"

namespace QM
{
	template <typename T = float>
	class complex
	{
	public:
		T re = 0;
		T im = 0;

		complex<T>(T x, T y) : re(x), im(y) {};

		T mod();
		double arg();

		complex<T> operator+(const complex<T>& right) const;
		void operator+=(const complex<T>& right);
		complex<T> operator-(const complex<T>& right) const;
		void operator-=(const complex<T>& right);
		complex<T> operator*(const complex<T>& right) const;
		void operator*=(const complex<T>& right);
		complex<T> operator/(const complex<T>& right) const;
		void operator/=(const complex<T>& right);



		complex<T> conjugate() const;
	};

	template<typename T>
	inline T complex<T>::mod()
	{
		return sqrt(re * re + im * im);
	}

	template<typename T>
	inline double complex<T>::arg()
	{
		double angle = 0;
		int sgn_y = 0;
		if (im < 0)
			sgn_y = -1;
		else if (im > 0)
			sgn_y = 1;

		if (re != 0)
			angle = atan(im / re);
		else
			return sgn_y * pi / 2;

		if (re > 0)
		{
			return angle;
		}
		else
			return angle + sgn_y * pi;
	}

	template<typename T>
	inline complex<T> complex<T>::conjugate() const
	{
		return complex<T>(re, -im);
	}

	template<typename T>
	inline complex<T> complex<T>::operator+(const complex<T>& right) const
	{
		return complex<T>(re + right.re, im + right.im);
	}

	template<typename T>
	inline void complex<T>::operator+=(const complex<T>& right)
	{
		re += right.re;
		im += right.im;
	}

	template<typename T>
	inline complex<T> complex<T>::operator-(const complex<T>& right) const
	{
		return complex<T>(re - right.re, im - right.im);
	}

	template<typename T>
	inline void complex<T>::operator-=(const complex<T>& right)
	{
		re -= right.re;
		im -= right.im;
	}

	template<typename T>
	inline complex<T> complex<T>::operator*(const complex<T>& right) const
	{
		return complex<T>(re * right.re - im * right.im, re * right.im + im * right.re);
	}

	template<typename T>
	inline void complex<T>::operator*=(const complex<T>& right)
	{
		re = re * right.re - im * right.im;
		im = re * right.im + im * right.re;
	}

	template<typename T>
	inline complex<T> complex<T>::operator/(const complex<T>& right) const
	{
		T denominator = (right * (right.conjugate())).re;		
		complex<T> numerator = (*this) * right.conjugate();
		return complex<T>(numerator.re/denominator, numerator.im/denominator);
	}

	template<typename T>
	inline void complex<T>::operator/=(const complex<T>& right)
	{
		T denominator = (right * (right.conjugate())).re;
		complex<T> numerator = (*this) * right.conjugate();
		re = numerator.re / denominator;
		im = numerator.im / denominator;
	}

}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, QM::complex<T> number)
{
	os << number.re;
	if (number.im >= 0)
		os << "+";
	os << number.im << "i";

	return os;
}

template<typename T>
inline QM::complex<T> sqrt(QM::complex<T> number)
{
	T gamma = sqrt((number.re + number.mod()) / 2);
	T delta = sqrt((-number.re + number.mod()) / 2) * abs(number.im)/number.im;
	return QM::complex<T>(gamma, delta);
}

template<typename T>
inline QM::complex<T> exp(QM::complex<T> number)
{
	
	return QM::complex<T>(round(100 * exp(number.re) * cos(number.im))/100, round(100*exp(number.re) * sin(number.im)));
}

template<typename T>
inline QM::complex<T> log(QM::complex<T> number)
{
	double phi = number.arg();
	while (phi > QM::pi)
		phi -= QM::pi;
	while (phi < -QM::pi)
		phi += QM::pi;

	return QM::complex<T>(log(number.mod()),(phi));
}

template<typename T>
inline QM::complex<T> pow(QM::complex<T> base, QM::complex<T> exponent)
{
	T E = exp(exponent * log(base.re));
	return QM::complex<T>(E * cos(base.im * exponent), E * sin(base.im * exponent));
}

template<typename T>
inline QM::complex<T> sin(QM::complex<T> number)
{
	return QM::complex<T>(sin(number.re) * cosh(number.im), cos(number.re) * sinh(number.im));
}

template<typename T>
inline QM::complex<T> cos(QM::complex<T> number)
{
	return QM::complex<T>(cos(number.re) * cosh(number.im), -sin(number.re) * sinh(number.im));
}

template<typename T>
inline QM::complex<T> tan(QM::complex<T> number)
{
	return sin(number) / cos(number);
}

template<typename T>
inline QM::complex<T> sinh(QM::complex<T> number)
{
	return QM::complex<T>(sinh(number.re) * cos(number.im), cosh(number.re) * sin(number.im));
}

template<typename T>
inline QM::complex<T> cosh(QM::complex<T> number)
{
	return QM::complex<T>(cosh(number.re) * cos(number.im), sinh(number.re) * sin(number.im));
}

template<typename T>
inline QM::complex<T> tanh(QM::complex<T> number)
{
	return sinh(number) / cosh(number);
}