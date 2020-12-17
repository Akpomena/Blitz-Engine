#pragma once
#include "Core.h"
#include "Window.h"

namespace BlitzEngine {

	class BLITZENGINE_API Application
	{
	public:
		Application();
		void Run();
		void OnEvent(Event& e);
		~Application() {};
	private:
		bool OnWindowClose(WindowClosedEvent e);
	private:
		bool m_IsRunning = true;
		Window m_Window;
	};

	Application* createApplication();
}

