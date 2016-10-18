#include "Rectangle.h"

namespace geo
{

	Rectangle::Rectangle(const double x, const double y, const double width, const double height)
	{
		
		Vertex aVertex1(x, y);
		Vertex aVertex2(x + width, y);
		Vertex aVertex3(x + width, y + height);
		Vertex aVertex4(x, y + height);

		m_vertices.push_back(aVertex1);
		m_vertices.push_back(aVertex2);
		m_vertices.push_back(aVertex3);
		m_vertices.push_back(aVertex4);

	}

	void Rectangle::draw(Renderer* aRenderer)
	{

		aRenderer->draw(this);

	}

}