#pragma once

// Logger only exists in debug mode
#ifdef DEBUG
#include <spdlog/spdlog.h>
#include <memory>
#include "core.h"

namespace BlitzEngine {

	class BLITZENGINE_API Logger
	{
	public:
		static void init();
		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return m_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return m_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};

}

#endif // DEBUG

#ifdef _DEBUG

#ifdef BLITZENGINE__EXPORTS
//Engine side logging
#define BLITZ_WARN(...) ::BlitzEngine::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define BLITZ_INFO(...) ::BlitzEngine::Logger::getCoreLogger()->info(__VA_ARGS__)
#define BLITZ_ERROR(...) ::BlitzEngine::Logger::getCoreLogger()->error(__VA_ARGS__)
#define BLITZ_TRACE(...) ::BlitzEngine::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define BLITZ_CRITICAL(...) ::BlitzEngine::Logger::getCoreLogger()->critical(__VA_ARGS__)
#else
//Client side logging
#define BLITZ_WARN(...) ::BlitzEngine::Logger::getClientLogger()->warn(__VA_ARGS__)
#define BLITZ_INFO(...) ::BlitzEngine::Logger::getClientLogger()->info(__VA_ARGS__)
#define BLITZ_ERROR(...) ::BlitzEngine::Logger::getClientLogger()->error(__VA_ARGS__)
#define BLITZ_TRACE(...) ::BlitzEngine::Logger::getClientLogger()->trace(__VA_ARGS__)
#define BLITZ_CRITICAL(...) ::BlitzEngine::Logger::getClientLogger()->critical(__VA_ARGS__)
#endif

#else
#define BLITZ_WARN(...)
#define BLITZ_INFO(...)
#define BLITZ_ERROR(...)
#define BLITZ_TRACE(...)
#define BLITZ_CRITICAL(...)

#endif // DEBUG
