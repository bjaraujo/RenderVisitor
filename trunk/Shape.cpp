
#include "Shape.h"

namespace geo
{

	Shape::Shape() : m_color(1.0, 1.0, 1.0)
	{

	}

	void Shape::addVertex(double x, double y)
	{

		Vertex aVertex(x, y);
		m_vertices.push_back(aVertex);

	}

	Vertex Shape::vertex(const int anIndex)
	{

		return m_vertices[anIndex];

	}

	void Shape::setColor(Color aColor)
	{
		m_color = aColor;
	}

	Color Shape::color()
	{
		return m_color;
	}

};

