#pragma once
extern BlitzEngine::Application* BlitzEngine::createApplication();

int main()
{
	auto app = BlitzEngine::createApplication();
	app->run();
	delete app;
}