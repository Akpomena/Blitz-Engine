#include "BlitzPch.h"
#include "application.h"
#include "Logger.h"
#include "../renderer/Renderer.h"
#include <chrono>
#include "../renderer/Box.h"

namespace BlitzEngine {
	
	bool pause = false;

	bool OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == VK_SPACE)
			pause = !pause;

		return true;
	}


	Application::Application() :
		m_Window(L"Blitz Engine", 800, 600, true)
	{
#ifdef DEBUG
		Logger::init();
#endif // DEBUG

		m_Window.SetEventCallback(BIND_FUNC(Application::OnEvent));
		m_Window.Init();

		auto [width, height] = m_Window.GetSize();
		if (!Renderer::Init(m_Window.GetWindow(), width, height))
			BLITZ_ERROR("Failed to initialize Renderer");

		BLITZ_INFO("Engine Successfully Initialized");
	}

	void Application::Run()
	{
		BLITZ_INFO("Engine Running...");

		MSG msg = {};
		auto start = std::chrono::steady_clock::now();
		
		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
		std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
		std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
		std::uniform_real_distribution<float> rdist(6.0f, 20.0f);

		std::vector<std::unique_ptr<Box>> boxes;
		for (int i = 0; i < 80; i++)
		{
			boxes.push_back(std::make_unique<Box>(
					rng, adist,
				ddist, odist, rdist
				));
		}
		
		while (m_IsRunning)
		{
			
			Renderer::ClearScreen(0.07f, 0.0f, 0.12f);

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> time = end - start;

			float update = 0.0f;
			for (auto& b : boxes)
			{
				if (pause)
					update = 0.0f;
				else
					update = time.count() * 0.001;

				b->Update(update);
				b->Draw();
			}

			Renderer::Present();

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
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_FUNC(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(BIND_FUNC(Application::OnWindowResized));
		dispatcher.Dispatch<KeyPressedEvent>(OnKeyPressed);
		
	}

	Application::~Application()
	{
		Renderer::ShutDown();
	}

	bool Application::OnWindowResized(WindowResizedEvent& e)
	{
		auto [width, height] = e.GetSize();

		if(Renderer::IsInitialized())
			Renderer::SetViewPort(width, height);

		return true;
	}

	bool Application::OnWindowClose(WindowClosedEvent e)
	{
		m_IsRunning = false;
	
		return true;
	}

}