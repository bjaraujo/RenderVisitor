
#include <iostream>
#include <thread>
#include <memory>

#include "Triangle.h"
#include "Rectangle.h"

#include "OpenGLRenderer.h"
#include "DirectXRenderer.h"
#include "ConsoleRenderer.h"

int OpenGLRenderer::m_width = 0;
int OpenGLRenderer::m_height = 0;

int DirectXRenderer::m_width = 0;
int DirectXRenderer::m_height = 0;

std::vector<std::shared_ptr<geo::Shape> > Renderer::m_shapes;

OpenGLRenderer* OpenGLRenderer::m_renderer = nullptr;
DirectXRenderer* DirectXRenderer::m_renderer = nullptr;
ConsoleRenderer* ConsoleRenderer::m_renderer = nullptr;

void renderTo(std::shared_ptr<Renderer> aRenderer, int argc, char* argv[], const char *title)
{

	aRenderer->initRendering(&argc, argv);

	aRenderer->createRenderingWindow(title);

	aRenderer->renderScene();

}

int main(int argc, char* argv[])
{

	auto aTriangle = std::make_shared<geo::Triangle>();
	aTriangle->addVertex(50, 50);
	aTriangle->addVertex(120, 150);
	aTriangle->addVertex(50, 200);
	aTriangle->setColor(geo::Color(1.0, 1.0, 0.0));

	auto aRectangle = std::make_shared<geo::Rectangle>(150, 50, 100, 200);
	aRectangle->setColor(geo::Color(0.0, 0.0, 1.0));

	Renderer::m_shapes.push_back(aTriangle);
	Renderer::m_shapes.push_back(aRectangle);

	auto anOpenGLRenderer = std::make_shared<OpenGLRenderer>(480, 480);
	OpenGLRenderer::m_renderer = anOpenGLRenderer.get();

	auto aDirectXRenderer = std::make_shared<DirectXRenderer>(480, 480);
	DirectXRenderer::m_renderer = aDirectXRenderer.get();

	auto aConsoleRenderer = std::make_shared<ConsoleRenderer>(480, 480);
	ConsoleRenderer::m_renderer = aConsoleRenderer.get();

	std::thread t1(renderTo, anOpenGLRenderer, argc, argv, "OpenGL");
	std::thread t2(renderTo, aDirectXRenderer, argc, argv, "DirectX");
	std::thread t3(renderTo, aConsoleRenderer, argc, argv, "Console");

	t1.join();
	t2.join();
	t3.join();

	return 0;

}