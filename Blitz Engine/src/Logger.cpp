#include "Logger.h"

namespace BlitzEngine {

	std::shared_ptr<spdlog::logger> Logger::m_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::m_ClientLogger;

	void Logger::init()
	{
		spdlog::set_pattern("%^ *** [%Y-%m-%d %H:%M:%S] [%n] %v *** %$");
		m_CoreLogger = spdlog::stdout_color_mt("Core");
		m_CoreLogger->set_level(spdlog::level::trace);

		m_ClientLogger = spdlog::stdout_color_mt("Client");
		m_ClientLogger->set_level(spdlog::level::trace);
	}
}