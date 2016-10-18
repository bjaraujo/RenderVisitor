
#include <iostream>

#include "Triangle.h"
#include "Rectangle.h"
#include "OpenGLRenderer.h"

int OpenGLRenderer::m_width = 0;
int OpenGLRenderer::m_height = 0;

std::vector<geo::Shape*> Renderer::m_shapes;
OpenGLRenderer* OpenGLRenderer::m_renderer = NULL;

int main(int argc, char* argv[])
{

	geo::Triangle aTriangle;

	aTriangle.setColor(geo::Color(1.0, 1.0, 0.0));
	aTriangle.addVertex(50, 50);
	aTriangle.addVertex(120, 150);
	aTriangle.addVertex(50, 200);

	geo::Rectangle aRectangle(150, 50, 100, 200);
	aRectangle.setColor(geo::Color(0.0, 0.0, 1.0));

	OpenGLRenderer anOpenGLRenderer(480, 480);

	OpenGLRenderer::m_renderer = &anOpenGLRenderer;

	anOpenGLRenderer.addShape(&aTriangle);
	anOpenGLRenderer.addShape(&aRectangle);

	anOpenGLRenderer.initRendering(&argc, argv);

	anOpenGLRenderer.createRenderingWindow("OpenGL Visitor Pattern Demo");

	anOpenGLRenderer.renderScene();

	return 0;

}