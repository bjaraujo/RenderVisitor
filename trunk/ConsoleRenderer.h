
#pragma once

#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"

#include "Renderer.h"

class ConsoleRenderer : public Renderer {

public:

	static ConsoleRenderer* m_renderer;

	ConsoleRenderer(int width, int height);

	static void drawShape(geo::Shape* aShape);

	void draw(geo::Triangle* aTriangle);
	void draw(geo::Rectangle* aRectangle);

	void initRendering(int *argc, char** argv);
	void createRenderingWindow(const char* title);
	void renderScene();

};
