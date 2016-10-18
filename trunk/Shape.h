#pragma once

#include "Renderer.h"

#include "Vertex.h"
#include "Color.h"

namespace geo
{

	class Shape {
	protected:

		Color m_color;
		std::vector<Vertex> m_vertices;

	public:

		Shape();

		virtual void draw(Renderer* aRenderer) = 0;
		
		void addVertex(double x, double y);
		Vertex vertex(const int anIndex);

		void setColor(Color aColor);
		Color color();

	};

}
