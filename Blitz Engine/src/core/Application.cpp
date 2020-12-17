#include "BlitzPch.h"
#include "application.h"
#include "Logger.h"

namespace BlitzEngine {

#define BIND_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application::Application() :
		m_Window(L"App Window", 800, 600)
	{
		Logger::init();
		m_Window.SetEventCallback(BIND_FUNC(OnEvent));
		m_Window.Init();
		BLITZ_INFO("Engine Successfully Initialized");
	}

	void Application::Run()
	{
		BLITZ_INFO("Engine Running...");

		MSG msg = {};
	
		while (m_IsRunning)
		{

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

		dis.Dispatch<WindowClosedEvent>(BIND_FUNC(OnWindowClose));
		
	}

	bool Application::OnWindowClose(WindowClosedEvent e)
	{
		m_IsRunning = false;
	
		return true;
	}

}