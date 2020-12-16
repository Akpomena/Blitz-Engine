#pragma once

#include "BlitzPch.h"
#include "Core.h"

namespace BlitzEngine {

	class BLITZENGINE_API Window
	{
	public:
		Window(const wchar_t* winName, uint32_t width, uint32_t height);
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		bool Init();
		HWND GetWindow() noexcept { return m_Hwnd; }
		~Window();

	public:
		//Deals with window messages
		static LRESULT CALLBACK WindowProcSetup(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept;
		static LRESULT CALLBACK WindowProcHandle(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept;
		LRESULT HandleEvent(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept;
	private:
		const wchar_t* m_WinName;
		uint32_t m_Width;
		uint32_t m_Height;

		HWND m_Hwnd; //window handle
	};

}


