#pragma once

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>

extern BlitzEngine::Application* BlitzEngine::createApplication();

void createDebugConsole();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	createDebugConsole();

	auto app = BlitzEngine::createApplication();
	app->Run();
	delete app;

	return 0;
}


void createDebugConsole()
{
	FILE* fp;
	AllocConsole();
	_wfreopen_s(&fp, L"CONOUT$", L"w", stdout);
	_wfreopen_s(&fp, L"CONIN$", L"r", stdin);
}

