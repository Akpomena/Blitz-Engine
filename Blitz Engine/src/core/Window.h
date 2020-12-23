#pragma once

#include "BlitzPch.h"
#include "Core.h"
#include "../event/KeyboardEvents.h"
#include "../event/WindowEvents.h"
#include "../event/MouseEvents.h"
#include "Graphics.h"

namespace BlitzEngine {

	using EVENTCALLBACK = std::function<void(Event&)>;

	class BLITZENGINE_API Window
	{
	public:
		Window(const wchar_t* winName, uint32_t width, uint32_t height);
		~Window();

		//Window class should not be copied
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool Init();
		inline void SetEventCallback(EVENTCALLBACK callback) noexcept { EventCallback = callback; }
		inline HWND GetWindow() const noexcept { return m_Hwnd; }
		inline const uint32_t& GetWidth() const noexcept { return m_Width; }
		inline const uint32_t& GetHeight() const noexcept { return m_Height; }

		//First value returned is the width position and the second is the height position
		inline std::pair<uint32_t, uint32_t> GetSize() const noexcept { return { m_Width, m_Height }; }

	public:
		//Deals with window messages
		static LRESULT CALLBACK WindowProcSetup(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept;
		static LRESULT CALLBACK WindowProcHandle(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept;
		LRESULT HandleEvent(HWND hwnd, UINT uMsg, WPARAM WParam, LPARAM LParam) noexcept;
		Graphics m_Gfx;
		float m_MouseXPos, m_MouseYPos;
	private:
		const wchar_t* m_WinName;
		uint32_t m_Width;
		uint32_t m_Height;
		EVENTCALLBACK EventCallback;

		HWND m_Hwnd; //window handle
	};

}


