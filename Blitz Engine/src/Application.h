#pragma once
#include "Core.h"

namespace BlitzEngine {

	class BLITZENGINE_API Application
	{
	public:
		Application();
		void init();
		void run();
		~Application() {};
	};

	Application* createApplication();
}

