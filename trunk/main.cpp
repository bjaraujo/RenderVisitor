
#include <iostream>
#include <thread>

#include "Triangle.h"
#include "Rectangle.h"

#include "OpenGLRenderer.h"
#include "DirectXRenderer.h"
#include "ConsoleRenderer.h"

int OpenGLRenderer::m_width = 0;
int OpenGLRenderer::m_height = 0;

int DirectXRenderer::m_width = 0;
int DirectXRenderer::m_height = 0;

std::vector<geo::Shape*> Renderer::m_shapes;

OpenGLRenderer* OpenGLRenderer::m_renderer = NULL;
DirectXRenderer* DirectXRenderer::m_renderer = NULL;
ConsoleRenderer* ConsoleRenderer::m_renderer = NULL;

void renderToOpenGL(int argc, char* argv[], const char *title)
{

	// OpenGL
	OpenGLRenderer anOpenGLRenderer(480, 480);

	OpenGLRenderer::m_renderer = &anOpenGLRenderer;

	anOpenGLRenderer.initRendering(&argc, argv);

	anOpenGLRenderer.createRenderingWindow(title);

	anOpenGLRenderer.renderScene();

}

void renderToDirectX(int argc, char* argv[], const char *title)
{

	// DirectX
	DirectXRenderer aDirectXRenderer(480, 480);

	DirectXRenderer::m_renderer = &aDirectXRenderer;

	aDirectXRenderer.initRendering(&argc, argv);

	aDirectXRenderer.createRenderingWindow(title);

	aDirectXRenderer.renderScene();

}

void renderToConsole(int argc, char* argv[], const char *title)
{

	// Console
	ConsoleRenderer aConsoleRenderer(480, 480);

	ConsoleRenderer::m_renderer = &aConsoleRenderer;

	aConsoleRenderer.initRendering(&argc, argv);

	aConsoleRenderer.createRenderingWindow(title);

	aConsoleRenderer.renderScene();

}

int main(int argc, char* argv[])
{

	geo::Triangle aTriangle;

	aTriangle.setColor(geo::Color(1.0, 1.0, 0.0));
	aTriangle.addVertex(50, 50);
	aTriangle.addVertex(120, 150);
	aTriangle.addVertex(50, 200);

	geo::Rectangle aRectangle(150, 50, 100, 200);
	aRectangle.setColor(geo::Color(0.0, 0.0, 1.0));

	Renderer::m_shapes.push_back(&aTriangle);
	Renderer::m_shapes.push_back(&aRectangle);

	std::thread t1(renderToOpenGL, argc, argv, "OpenGL");
	std::thread t2(renderToDirectX, argc, argv, "DirectX");
	std::thread t3(renderToConsole, argc, argv, "Console");

	t1.join();
	t2.join();
	t3.join();

	return 0;

}