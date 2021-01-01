#pragma once

#include "Event.h"

namespace BlitzEngine {

	class BLITZENGINE_API WindowClosedEvent : public Event
	{
	public:

		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Window Close";

			return ss.str();
		}

		EVENT_TYPE(EventType::WINDOWCLOSED)
	};

	class BLITZENGINE_API WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(uint32_t width, uint32_t height, bool minimized) noexcept :
			m_Width(width), m_Height(height), m_IsMinimized(minimized) {}

		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Window Resized Width: " << m_Width << " Height: " << m_Height << " Minimized: " << m_IsMinimized;

			return ss.str();
		}

		inline bool IsMinimized() const noexcept { return m_IsMinimized; }
		inline uint32_t GetWidth() const noexcept { return m_Width; }
		inline uint32_t GetHeight() const noexcept { return m_Height; }
		inline std::pair<uint32_t, uint32_t> GetSize() const noexcept { return {m_Width, m_Height}; }

		EVENT_TYPE(EventType::WINDOWRESIZED);
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		bool m_IsMinimized;
	};

}