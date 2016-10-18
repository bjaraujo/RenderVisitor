
#pragma once

#include <vector>

namespace geo
{
	class Shape;
	class Triangle;
	class Rectangle;
}

class Renderer {

protected:
	
	static std::vector<geo::Shape*> m_shapes;

public:

	static void addShape(geo::Shape* aShape);
	
	virtual void draw(geo::Triangle* aTriangle) = 0;
	virtual void draw(geo::Rectangle* aRectangle) = 0;

	virtual void initRendering(int *argc, char** argv) = 0;
	virtual void createRenderingWindow(const char* title) = 0;

	virtual void renderScene() = 0;

};

