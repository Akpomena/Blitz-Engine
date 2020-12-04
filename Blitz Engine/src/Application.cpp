#include "application.h"
#include <iostream>

namespace BlitzEngine {

	Application::Application()
	{
		init();
	}

	void Application::run()
	{
		std::cout << "Engine Running" << std::endl;
		std::cin.get();
	}

	void Application::init()
	{
		std::cout << "Engine Initialized" << std::endl;
	}

}