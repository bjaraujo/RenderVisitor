
#include "Vertex.h"

namespace geo
{

	Vertex::Vertex(double x, double y) : m_x(x), m_y(y)
	{

	}

	double Vertex::x()
	{
		return m_x;
	}

	double Vertex::y()
	{
		return m_y;
	}

}
