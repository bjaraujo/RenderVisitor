#pragma once

#include "Shape.h"

namespace geo
{

	class Rectangle : public Shape {

	public:

		Rectangle(const double x, const double y, const double width, const double height);

		void draw(Renderer* aRenderer);

		// C++11 delete
		void addVertex(double x, double y) = delete;

	};

}