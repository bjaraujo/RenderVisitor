
#include "Color.h"

namespace geo
{

	Color::Color(double r, double g, double b) : m_r(r), m_g(g), m_b(b)
	{

	}

	double Color::r()
	{
		return m_r;
	}

	double Color::g()
	{
		return m_g;
	}

	double Color::b()
	{
		return m_b;
	}
	
}
