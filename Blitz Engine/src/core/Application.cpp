#include "BlitzPch.h"

#include "application.h"
#include "Logger.h"

namespace BlitzEngine {

	Application::Application() :
		m_Window(L"App Window", 800, 600)
	{
		Logger::init();
		m_Window.Init();
		BLITZ_INFO("Engine Successfully Initialized");
	}

	void Application::run()
	{
		BLITZ_INFO("Engine Running...");
		std::cin.get();
	}

}