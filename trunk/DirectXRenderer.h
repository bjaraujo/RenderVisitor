
#pragma once

#include<windows.h> 
#include<d3d9.h> 

#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"

#include "Renderer.h"

class DirectXRenderer : public Renderer {

private:
	static int m_width;
	static int m_height;

	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pdx_VB;
	HWND m_han_Window;

	static LRESULT CALLBACK ourWindowProcedure(HWND han_Wind, UINT uint_Message, WPARAM parameter1, LPARAM parameter2);
	LPDIRECT3DDEVICE9 initializeDevice(HWND han_WindowToBindTo);
	void drawScene();

public:

	static DirectXRenderer* m_renderer;

	DirectXRenderer(int width, int height);

	static void drawShape(geo::Shape* aShape);

	void draw(geo::Triangle* aTriangle);
	void draw(geo::Rectangle* aRectangle);

	void initRendering(int *argc, char** argv);
	void createRenderingWindow(const char* title);
	void renderScene();

};
