#pragma once

extern BlitzEngine::Application* BlitzEngine::createApplication();


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	auto app = BlitzEngine::createApplication();
	app->Run();
	delete app;

	return 0;
}
