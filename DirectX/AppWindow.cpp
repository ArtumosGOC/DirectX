#include "AppWindow.h"

struct vector3d
{
	float x, y, z;
};
struct vertex
{
	vector3d position;
};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] = {
		
		{-0.5f,-0.5f,0.0f}, 
		{-0.5f,0.5f,0.0f},
		{ 0.5f,0.5f,0.0f},

		{0.5f,0.5f,0.0f},
		{0.5f,-0.5f,0.0f},
		{ -0.5f,-0.5f,0.0f}
		
		

	};
	m_VertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);
	

	GraphicsEngine::get()->createShaders();
	void* shader_bcode = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_bcode, &size_shader);
	m_VertexBuffer->load(list,sizeof(vertex), size_list, shader_bcode, size_shader);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->setShaders();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_VertexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_VertexBuffer->getSizeVertexList(),0);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_VertexBuffer->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}