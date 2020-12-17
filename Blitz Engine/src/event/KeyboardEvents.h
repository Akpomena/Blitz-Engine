#pragma once

#include "Event.h"

namespace BlitzEngine {

	class BLITZENGINE_API KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(int keycode) noexcept : m_Keycode(keycode) {}
		
		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Key Pressed " << m_Keycode;

			return ss.str();
		}

		int& GetKeyCode() noexcept { return m_Keycode; }

		EVENT_TYPE(EventType::KEYPRESSED)
	private:
		int m_Keycode;
	};

	class BLITZENGINE_API KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int keycode) noexcept : m_Keycode(keycode) {}
		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Key Released " << m_Keycode;

			return ss.str();
		}

		inline int& GetKeyCode() noexcept { return m_Keycode; }

		EVENT_TYPE(EventType::KEYRELEASED)
	private:
		int m_Keycode;
	};

	class BLITZENGINE_API KeyTypedEvent : public Event
	{
	public:
		KeyTypedEvent(int keycode) noexcept : m_Keycode(keycode) {}
		
		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Key Typed " << m_Keycode;

			return ss.str();
		}

		inline int& GetKeyCode() noexcept { return m_Keycode; }

		EVENT_TYPE(EventType::KEYTYPED)
	private:
		int m_Keycode;
	};

}