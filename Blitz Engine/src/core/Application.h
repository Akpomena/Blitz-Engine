#pragma once
#include "Core.h"
#include "Window.h"

namespace BlitzEngine {

	class BLITZENGINE_API Application
	{
	public:
		Application();
		void run();
		~Application() {};
	private:
		Window m_Window;
	};

	Application* createApplication();
}

