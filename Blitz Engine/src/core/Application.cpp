#include "BlitzPch.h"
#include "application.h"
#include "Logger.h"

namespace BlitzEngine {
	
	Application::Application() :
		m_Window(L"App Window", 800, 600)
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
	
		while (m_IsRunning)
		{

			m_Window.m_Gfx.ClearScreen(1.0f, 0.0f, 0.0f);
			m_Window.m_Gfx.DrawTriangle();

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