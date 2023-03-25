#pragma once

//temporary file, these will later be transfered to QGraphics
//where the z-axis will need inverting

#include "Core.h"
#include "Matrix.h"

namespace QM
{
	class /*[[deprecated]]*/ Orthographic : public matrix<4,4,float>
	{
	private:
		int Top, Bottom, Near, Far, Left, Right;
	public:
		Orthographic(int left, int right, int bottom, int top, int near, int far) : Left(left), Right(right), Bottom(bottom), Top(top), Near(near),Far(far)
		{
			this->set(1, 1, 2 / ((float)Right - (float)Left));
			this->set(1, 4, -((float)Right + (float)Left) / ((float)Right - (float)Left));
			this->set(2, 2, 2 / ((float)Top - (float)Bottom));
			this->set(2, 4, -((float)Top + (float)Bottom) / ((float)Top - (float)Bottom));
			this->set(3, 3, -2 / ((float)Far - (float)Near));
			this->set(3, 4, -((float)Far + (float)Near) / ((float)Far - (float)Near));
			this->set(4, 4, 1);
		};
	};

	class /*[[deprecated]]*/ Perspective : public matrix<4,4,float>
	{
	private:
		double m_fovy, m_aspect, m_near, m_far;
	public:
		Perspective(double fovy, double aspect, double near, double far) : m_fovy(fovy), m_aspect(aspect), m_near(near), m_far(far)
		{
			this->set(1, 1, 1.0f / ((float)m_aspect * (float)tan(rad((float)m_fovy / 2))));
			this->set(2, 2, 1.0f / ((float)tan(rad((float)m_fovy / 2))));
			this->set(3, 3, ((float)m_far + (float)m_near) / ((float)m_near - (float)m_far));
			this->set(3, 4, 2 * (float)m_far * (float)m_near / ((float)m_near - (float)m_far));
			this->set(4, 3, -1.0f);
		};
	};
}
