#include "application.h"
#include "EntryPoint.h"


class SandboxApp : public BlitzEngine::Application
{
public:
	SandboxApp() {};
	~SandboxApp() {};
};

BlitzEngine::Application* BlitzEngine::createApplication()
{
	return new SandboxApp;
}