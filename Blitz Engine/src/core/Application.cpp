#include "BlitzPch.h"
#include "application.h"
#include "Logger.h"
#include <chrono>

namespace BlitzEngine {
	
	Application::Application() :
		m_Window(L"Blitz Engine", 800, 600)
	{
		Logger::init();
		m_Window.SetEventCallback(BIND_FUNC(Application::OnEvent));
		m_Window.Init();
		BLITZ_INFO("Engine Successfully Initialized");
	}

	void Application::Run()
	{
		BLITZ_INFO("Engine Running...");

		MSG msg = {};
		auto start = std::chrono::steady_clock::now();
		while (m_IsRunning)
		{
			
			m_Window.m_Gfx.ClearScreen(1.0f, 0.0f, 0.0f);

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> time = end - start;

			float x = (m_Window.m_MouseXPos / 400.0f) - 1;
			float y = (-m_Window.m_MouseYPos / 300.0f) + 1;
			m_Window.m_Gfx.DrawTriangle(x, y, time.count());

			//Check for messages in the message queue
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
		
		
		}
	}

	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dis(e);

		dis.Dispatch<WindowClosedEvent>(BIND_FUNC(Application::OnWindowClose));
		
	}

	bool Application::OnWindowClose(WindowClosedEvent e)
	{
		m_IsRunning = false;
	
		return true;
	}

}