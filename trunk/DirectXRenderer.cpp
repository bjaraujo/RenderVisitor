
#include "DirectXRenderer.h"

struct OURCUSTOMVERTEX
{
	float x, y, z, weight;
	DWORD color;
};

DirectXRenderer::DirectXRenderer(int width, int height)
{

	DirectXRenderer::m_width = width;
	DirectXRenderer::m_height = height;

}

void DirectXRenderer::initRendering(int *argc, char** argv) {


}

LRESULT CALLBACK DirectXRenderer::ourWindowProcedure(HWND han_Wind, UINT uint_Message, WPARAM parameter1, LPARAM parameter2)
{
	switch (uint_Message)
	{
	case WM_KEYDOWN:
	{
		//int_AppRunning = 0;
		break;
	}
	break;
	}

	return DefWindowProc(han_Wind, uint_Message, parameter1, parameter2);

}

LPDIRECT3DDEVICE9 DirectXRenderer::initializeDevice(HWND han_WindowToBindTo)
{
	LPDIRECT3D9 p_dx_Object;
	LPDIRECT3DDEVICE9 p_dx_Device;

	p_dx_Object = Direct3DCreate9(D3D_SDK_VERSION);
	if (p_dx_Object == NULL)
	{
		MessageBox(han_WindowToBindTo, "DirectX Runtime library not installed!", "InitializeDevice()", MB_OK);
	}

	D3DPRESENT_PARAMETERS dx_PresParams;
	ZeroMemory(&dx_PresParams, sizeof(dx_PresParams));
	dx_PresParams.Windowed = TRUE;
	dx_PresParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	dx_PresParams.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(p_dx_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, han_WindowToBindTo, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dx_PresParams, &p_dx_Device)))
	{
		if (FAILED(p_dx_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, han_WindowToBindTo, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &dx_PresParams, &p_dx_Device)))
		{
			MessageBox(han_WindowToBindTo, "Failed to create even the reference device!", "InitializeDevice()", MB_OK);
		}
	}

	return p_dx_Device;
}

LPDIRECT3DVERTEXBUFFER9 DirectXRenderer::fillVertices(HWND han_Window, LPDIRECT3DDEVICE9 p_dx_Device)
{

	OURCUSTOMVERTEX cv_Vertices[3];
	LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer;

	cv_Vertices[0].x = 150;
	cv_Vertices[0].y = 100;
	cv_Vertices[0].z = 0;
	cv_Vertices[0].weight = 1;
	cv_Vertices[0].color = 0xffff0000;

	cv_Vertices[1].x = 350;
	cv_Vertices[1].y = 100;
	cv_Vertices[1].z = 0;
	cv_Vertices[1].weight = 1;
	cv_Vertices[1].color = 0xff00ff00;

	cv_Vertices[2].x = 250;
	cv_Vertices[2].y = 300;
	cv_Vertices[2].z = 0;
	cv_Vertices[2].weight = 1;
	cv_Vertices[2].color = 0xff00ffff;

	if (FAILED(p_dx_Device->CreateVertexBuffer(3 * sizeof(OURCUSTOMVERTEX), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL)))
	{
		MessageBox(han_Window, "Error while creating VertexBuffer", "fillVertices()", MB_OK);
	}

	VOID* p_Vertices;
	if (FAILED(p_dx_VertexBuffer->Lock(0, 3 * sizeof(OURCUSTOMVERTEX), (void**)&p_Vertices, 0)))
	{
		MessageBox(han_Window, "Error trying to lock", "fillVertices()", MB_OK);
	}
	else{
		memcpy(p_Vertices, cv_Vertices, 3 * sizeof(OURCUSTOMVERTEX));
		p_dx_VertexBuffer->Unlock();
	}

	return p_dx_VertexBuffer;

}

void DirectXRenderer::createRenderingWindow(const char* title) {


	WNDCLASSEX wnd_Structure;

	wnd_Structure.cbSize = sizeof(WNDCLASSEX);
	wnd_Structure.style = CS_HREDRAW | CS_VREDRAW;
	wnd_Structure.lpfnWndProc = ourWindowProcedure;
	wnd_Structure.cbClsExtra = 0;
	wnd_Structure.cbWndExtra = 0;
	wnd_Structure.hInstance = GetModuleHandle(NULL);
	wnd_Structure.hIcon = NULL;
	wnd_Structure.hCursor = NULL;
	wnd_Structure.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
	wnd_Structure.lpszMenuName = NULL;
	wnd_Structure.lpszClassName = "WindowClassName";
	wnd_Structure.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wnd_Structure);

	m_han_Window = CreateWindowEx(WS_EX_CONTROLPARENT, "WindowClassName", title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WS_SIZEBOX,
		0, 0, DirectXRenderer::m_width, DirectXRenderer::m_height, NULL, NULL, GetModuleHandle(NULL), NULL);

	m_pDevice = initializeDevice(m_han_Window);
	m_pdx_VB = fillVertices(m_han_Window, m_pDevice);

}

void DirectXRenderer::drawScene()
{

	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	m_pDevice->BeginScene();

	// C++11 auto and range
	for (auto s : DirectXRenderer::m_shapes)
		DirectXRenderer::drawShape(s);

	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);

}

void DirectXRenderer::renderScene() {

	MSG msg_Message;

	while (true)
	{
		if (PeekMessage(&msg_Message, m_han_Window, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg_Message);
		}
		drawScene();
	}

	m_pDevice->Release();
	DestroyWindow(m_han_Window);

}


void DirectXRenderer::drawShape(geo::Shape* aShape)
{

	aShape->draw(m_renderer);

}

void DirectXRenderer::draw(geo::Triangle* aTriangle)
{

	OURCUSTOMVERTEX cv_Vertices[3];
	LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer;

	for (size_t i = 0; i < aTriangle->nbVertices(); i++)
	{
		cv_Vertices[i].x = (float)aTriangle->vertex(i).x();
		cv_Vertices[i].y = (float)aTriangle->vertex(i).y();
		cv_Vertices[i].z = 0;
		cv_Vertices[i].weight = 1;
		cv_Vertices[i].color = (((int)(aTriangle->color().r() * 255) & 0xff) << 16) | (((int)(aTriangle->color().g() * 255) & 0xff) << 8) | ((int)(aTriangle->color().b() * 255) & 0xff);
	}
	
	m_pDevice->CreateVertexBuffer(aTriangle->nbVertices() * sizeof(OURCUSTOMVERTEX), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL);

	VOID* p_Vertices;
	p_dx_VertexBuffer->Lock(0, aTriangle->nbVertices() * sizeof(OURCUSTOMVERTEX), (void**)&p_Vertices, 0);

	memcpy(p_Vertices, cv_Vertices, aTriangle->nbVertices() * sizeof(OURCUSTOMVERTEX));
	p_dx_VertexBuffer->Unlock();

	m_pDevice->SetStreamSource(0, p_dx_VertexBuffer, 0, sizeof(OURCUSTOMVERTEX));
	m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

}

void DirectXRenderer::draw(geo::Rectangle* aRectangle)
{

	OURCUSTOMVERTEX cv_Vertices[4];
	LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer;

	for (size_t i = 0; i < aRectangle->nbVertices(); i++)
	{
		cv_Vertices[i].x = (float)aRectangle->vertex(i).x();
		cv_Vertices[i].y = (float)aRectangle->vertex(i).y();
		cv_Vertices[i].z = 0;
		cv_Vertices[i].weight = 1;
		cv_Vertices[i].color = (((int)(aRectangle->color().r() * 255) & 0xff) << 16) | (((int)(aRectangle->color().g() * 255) & 0xff) << 8) | ((int)(aRectangle->color().b() * 255) & 0xff);
	}

	m_pDevice->CreateVertexBuffer(aRectangle->nbVertices() * sizeof(OURCUSTOMVERTEX), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL);

	VOID* p_Vertices;
	p_dx_VertexBuffer->Lock(0, aRectangle->nbVertices() * sizeof(OURCUSTOMVERTEX), (void**)&p_Vertices, 0);

	memcpy(p_Vertices, cv_Vertices, aRectangle->nbVertices() * sizeof(OURCUSTOMVERTEX));
	p_dx_VertexBuffer->Unlock();

	m_pDevice->SetStreamSource(0, p_dx_VertexBuffer, 0, sizeof(OURCUSTOMVERTEX));
	m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}




