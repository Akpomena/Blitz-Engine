#pragma once

#include "Event.h"

namespace BlitzEngine
{

	class BLITZENGINE_API MouseEvent : public Event
	{
	public:
		virtual const int& GetXPos() const final { return m_XPos; }
		virtual const int& GetYPos() const final { return m_YPos; }

		//First value returned is the x position and the second is the y position
		virtual std::pair<int, int> GetPosition() const final { return { m_XPos, m_YPos }; }

	protected:
		MouseEvent(int xPos, int yPos) noexcept :
			m_XPos(xPos), m_YPos(yPos) {}
	private:
		int m_XPos, m_YPos;
	};

	class BLITZENGINE_API MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(int xPos, int yPos) noexcept :
			MouseEvent(xPos, yPos) {}

		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Mouse Moved XPOS: " << GetXPos() << " YPOS: " << GetYPos();
			return ss.str();
		}

		EVENT_TYPE(EventType::MOUSEMOVED)
	};

	class BLITZENGINE_API MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(float yDelta, float xDelta, int xPos, int yPos) noexcept :
			MouseEvent(xPos, yPos), m_YDelta(yDelta), m_XDelta(xDelta) {}

		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled XPOS: " << GetXPos() << " YPOS: " << GetYPos() << " Delta: " << m_YDelta << " "
				<< m_XDelta;
			return ss.str();
		}

		inline const float& GetYDelta() const noexcept { return m_YDelta; }
		inline const float& GetXDelta() const noexcept { return m_YDelta; }

		inline std::pair<int, int> GetDelta() const noexcept { return { m_XDelta, m_YDelta }; }

		EVENT_TYPE(EventType::MOUSESCROLLED)
	private:
		float m_YDelta, m_XDelta;
	};

	class BLITZENGINE_API MousePressedEvent: public MouseEvent
	{
	public:
		MousePressedEvent(int mouseCode, int xPos, int yPos) noexcept :
			MouseEvent(xPos, yPos), m_MouseCode(mouseCode) {}

		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Mouse Pressed XPOS: " << GetXPos() << " YPOS: " << GetYPos() << " Button: " << m_MouseCode;
			return ss.str();
		}

		inline const int& GetMouseCode() const noexcept { return m_MouseCode; }

		EVENT_TYPE(EventType::MOUSEPRESSED)
	private:
		int m_MouseCode;
	};

	class BLITZENGINE_API MouseReleasedEvent : public MouseEvent
	{
	public:
		MouseReleasedEvent(int mouseCode, int xPos, int yPos) noexcept :
			MouseEvent(xPos, yPos), m_MouseCode(mouseCode) {}

		virtual std::string EventInfo() const noexcept override
		{
			std::stringstream ss;
			ss << "Mouse Released XPOS: " << GetXPos() << " YPOS: " << GetYPos() << " Button: " << m_MouseCode;
			return ss.str();
		}

		inline const int& GetMouseCode() const noexcept { return m_MouseCode; }

		EVENT_TYPE(EventType::MOUSERELEASED)
	private:
		int m_MouseCode;
	};

}