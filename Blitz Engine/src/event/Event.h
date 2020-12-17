#pragma once

#include "../core/Core.h"
#include "BlitzPch.h"


namespace BlitzEngine {

	enum class EventType
	{
		none = 0, 
		KEYPRESSED, KEYRELEASED, KEYTYPED,
		MOUSESCROLLED, MOUSEPRESSED, MOUSERELEASED, MOUSEMOVED,
		WINDOWRESIZED, WINDOWCLOSED
	};

#define EVENT_TYPE(type) virtual EventType GetEventType() noexcept override { return type; }\
								static EventType GetStaticType() noexcept { return type; }


	class BLITZENGINE_API Event
	{
	public:
		virtual EventType GetEventType() noexcept = 0;
		virtual std::string EventInfo() const noexcept = 0;
	};


	class BLITZENGINE_API EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_Event(e) {}

		template <typename T>
		bool Dispatch(std::function<bool(T&)> func)
		{
			//Checks if the event passed in is the the same as the event being dispatched
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//Cast event to the apropriate event and calls func on it
				func(*(T*)&m_Event);
				return true;
			}

			return false;
		}
	private:
		Event& m_Event;
	};

}