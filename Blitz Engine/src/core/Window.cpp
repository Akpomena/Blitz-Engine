#include "BlitzPch.h"

#include "Window.h"
#include "Logger.h"

namespace BlitzEngine {

	Window::Window(const wchar_t* winName, uint32_t width, uint32_t height) :
		m_WinName(winName), m_Width(width), m_Height(height)
	{
	}

	bool Window::Init()
	{
		const wchar_t* CLASS_NAME = L"Blitz Engine Window";

		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = Window::WindowProcSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = CLASS_NAME;
		wc.hIconSm = nullptr;

		RegisterClassEx(&wc);

		m_Hwnd = CreateWindowEx(
			0,
			CLASS_NAME,
			m_WinName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			m_Width,
			m_Height,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			this
			);


		ShowWindow(m_Hwnd, SW_SHOWDEFAULT);

		return false;
	}

	Window::~Window()
	{
		UnregisterClass(L"Blitz Engine Window", GetModuleHandle(nullptr));
		DestroyWindow(m_Hwnd);
	}

	LRESULT Window::WindowProcSetup(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept
	{
		if (uMsg == WM_NCCREATE)
		{
			//Retrieve the createstruct structure 
			const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(LParam);

			//Retrive the window passed into the createwindow function
			Window* const pWindow = static_cast<Window*>(pCreate->lpCreateParams);

			//Set this window to the window user data
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));

			//Set WindowProcHandle as new windowproc
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Window::WindowProcHandle));

		}

		return DefWindowProc(hwnd, uMsg, WParam, LParam);
	}

	LRESULT Window::WindowProcHandle(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept
	{
		Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		return pWindow->HandleEvent(hwnd, uMsg, WParam, LParam);
	}

	LRESULT Window::HandleEvent(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hwnd, uMsg, WParam, LParam);
	}
}