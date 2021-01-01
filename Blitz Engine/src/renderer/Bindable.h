#pragma once
#include "../core/Core.h"

namespace BlitzEngine {

	class BLITZENGINE_API Bindable
	{
	public:
		virtual void Bind() noexcept = 0;
	};

}