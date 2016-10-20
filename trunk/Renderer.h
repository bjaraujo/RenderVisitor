
#pragma once

#include <memory>
#include <vector>

namespace geo
{
	class Shape;
	class Triangle;
	class Rectangle;
}

class Renderer {

public:

	static std::vector<std::shared_ptr<geo::Shape> > m_shapes;

	virtual void draw(geo::Triangle* aTriangle) = 0;
	virtual void draw(geo::Rectangle* aRectangle) = 0;

	virtual void initRendering(int *argc, char** argv) = 0;
	virtual void createRenderingWindow(const char* title) = 0;

	virtual void renderScene() = 0;

};

