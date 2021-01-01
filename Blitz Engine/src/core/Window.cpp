#include "BlitzPch.h"

#include "Window.h"
#include "Logger.h"

namespace BlitzEngine {

	Window::Window(const wchar_t* winName, uint32_t width, uint32_t height) :
		m_WinName(winName), m_Width(width), m_Height(height), m_Hwnd(nullptr), 
		m_MouseXPos(0.0f), m_MouseYPos(0.0f)
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

		RECT cw = { 0 };
		cw.left = 0;
		cw.right = cw.left + m_Width;
		cw.top = 0;
		cw.bottom = cw.top + m_Height;

		//Adjust to ensure client area is same size  as window class was initialized
		AdjustWindowRectEx(&cw, WS_OVERLAPPEDWINDOW, false, 0);

		m_Hwnd = CreateWindowEx(
			0,
			CLASS_NAME,
			m_WinName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			cw.right - cw.left,
			cw.bottom - cw.top,
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
		/*
		* RETRIVES THE WINDOW FROM USERDATA SET IN THE PREVIOUS WINDOW PROCEDURE AND
		* FORWARDS THE MESSAGE TO THE CLASS INSTANCE PROCEDURE 
		*/

		Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		return pWindow->HandleEvent(hwnd, uMsg, WParam, LParam);
	}

	LRESULT Window::HandleEvent(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept
	{
		switch (uMsg)
		{
		case WM_CLOSE:
		{
			WindowClosedEvent e;
			EventCallback(e);
			return 0;
		}

		case WM_SIZE:
		{
			UINT width = LOWORD(LParam);
			UINT height = HIWORD(LParam);
			bool minimize = WParam == SIZE_MINIMIZED;

			//Update the window member variables
			m_Width = width;
			m_Height = height;

			WindowResizedEvent e(width, height, minimize);
			EventCallback(e);
			break;
		}

		case WM_KEYDOWN:
		{
			KeyPressedEvent e((int)WParam);
			EventCallback(e);
			break;
		}

		case WM_KEYUP:
		{
			KeyReleasedEvent e((int)WParam);
			EventCallback(e);
			break;
		}

		case WM_CHAR:
		{
			KeyTypedEvent e((int)WParam);
			EventCallback(e);
			break;
		}

		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(LParam);
			m_MouseXPos = pt.x;
			m_MouseYPos = pt.y;
			MouseMovedEvent e(pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_MOUSEWHEEL:
		{
			POINTS pt = MAKEPOINTS(LParam);
			short delta = GET_WHEEL_DELTA_WPARAM(WParam);
			MouseScrolledEvent e(delta / 120.0f, 0.0f, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_MOUSEHWHEEL:
		{
			POINTS pt = MAKEPOINTS(LParam);
			short delta = GET_WHEEL_DELTA_WPARAM(WParam);
			MouseScrolledEvent e(0.0f, delta / 120.0f, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_LBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(LParam);
			MousePressedEvent e(VK_LBUTTON, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_RBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(LParam);
			MousePressedEvent e(VK_RBUTTON, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_MBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(LParam);
			MousePressedEvent e(VK_MBUTTON, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_LBUTTONUP:
		{
			POINTS pt = MAKEPOINTS(LParam);
			MouseReleasedEvent e(VK_LBUTTON, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_RBUTTONUP:
		{
			POINTS pt = MAKEPOINTS(LParam);
			MouseReleasedEvent e(VK_RBUTTON, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		case WM_MBUTTONUP:
		{
			POINTS pt = MAKEPOINTS(LParam);
			MouseReleasedEvent e(VK_MBUTTON, pt.x, pt.y);
			EventCallback(e);
			break;
		}

		}

		return DefWindowProc(hwnd, uMsg, WParam, LParam);
	}
}