
#pragma once

#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"

#include "Renderer.h"

class OpenGLRenderer : public Renderer {

private:
	static int m_width;
	static int m_height;

	static void update();
	static void display();
	static void reshape(int width, int height);

public:

	static OpenGLRenderer* m_renderer;

	OpenGLRenderer(int width, int height);

	static void drawShape(geo::Shape* aShape);

	void draw(geo::Triangle* aTriangle);
	void draw(geo::Rectangle* aRectangle);

	void initRendering(int *argc, char** argv);
	void createRenderingWindow(const char* title);
	void renderScene();

};
