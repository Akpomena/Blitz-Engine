#pragma once

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <windows.h>

extern BlitzEngine::Application* BlitzEngine::createApplication();

void createDebugConsole();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	createDebugConsole();

	auto app = BlitzEngine::createApplication();
	
	MSG msg = {};
	int check;
	while (check = GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (check == -1)
		return -1;

	app->run();
	delete app;

	return msg.wParam;
}


void createDebugConsole()
{
	FILE* fp;
	AllocConsole();
	_wfreopen_s(&fp, L"CONOUT$", L"w", stdout);
	_wfreopen_s(&fp, L"CONIN$", L"r", stdin);
}