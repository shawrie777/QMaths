#pragma once

#include <math.h>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace QM
{
	constexpr double pi = 3.14159265358979323846264338327950288;
	constexpr double e = 2.71828182845904523536028747135266249;

	double rad(double angle);
	double deg(double angle);

	void rangeCheck(double& angle, bool rad = true);
}