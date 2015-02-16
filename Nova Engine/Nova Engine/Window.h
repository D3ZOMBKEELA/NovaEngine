#pragma once

#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	void Initialize(LPCSTR title);
	void Shutdown();

	HWND GetHwnd() { return m_hWnd; }
	HINSTANCE GetHinstance() { return m_hInstance; };

private:
	LPCSTR m_title;
	HWND m_hWnd;
	HINSTANCE m_hInstance;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);