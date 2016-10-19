
#include <iostream>

#include "ConsoleRenderer.h"

using namespace std;

ConsoleRenderer::ConsoleRenderer(int width, int height)
{


}

void ConsoleRenderer::initRendering(int *argc, char** argv) {

}

void ConsoleRenderer::createRenderingWindow(const char* title) {

}

void ConsoleRenderer::renderScene() {

	// C++11 auto and range
	for (auto s : m_shapes)
		drawShape(s);

}

void ConsoleRenderer::drawShape(geo::Shape* aShape)
{

	aShape->draw(m_renderer);

}

void ConsoleRenderer::draw(geo::Triangle* aTriangle)
{

	cout << "Draw triangle." << endl;

}

void ConsoleRenderer::draw(geo::Rectangle* aRectangle)
{

	cout << "Draw rectangle." << endl;

}




