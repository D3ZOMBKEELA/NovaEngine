#include "Window.h"

Window::Window() {}
Window::~Window() {}

void Window::Initialize(LPCSTR title)
{
	WNDCLASSEX wc;

	m_title = title;

	m_hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_title;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_title, m_title, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 0, 0, 1920, 1080, NULL, NULL, m_hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void Window::Shutdown()
{
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	UnregisterClass(m_title, m_hInstance);
	m_hInstance = NULL;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
}