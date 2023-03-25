#include "Core.h"

namespace QM
{
	double QM::rad(double angle)
	{
		return angle * pi / 180;
	}

	double QM::deg(double angle)
	{
		return angle * 180 / pi;
	}

	void rangeCheck(double& angle, bool rad)
	{
		if (rad)
		{
			while (angle < 0)
				angle += 2 * pi;
			while (angle > 2 * pi)
				angle -= 2 * pi;
		}
		else
		{
			while (angle < 0)
				angle += 360;
			while (angle > 360)
				angle -= 360;
		}
	}
}