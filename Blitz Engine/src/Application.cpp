#include <iostream>

#include "application.h"
#include "Logger.h"

namespace BlitzEngine {

	Application::Application()
	{
		std::cout << "Engine Initialized" << std::endl;
		Logger::init();
	}

	void Application::run()
	{
		std::cout << "Engine Running" << std::endl;
		BLITZ_WARN("This is a warning");
		BLITZ_INFO("This is a info");
		BLITZ_ERROR("This is an Error");
		BLITZ_TRACE("This is a Trace");
		BLITZ_CRITICAL("This is a critacal");
		std::cin.get();
	}

}