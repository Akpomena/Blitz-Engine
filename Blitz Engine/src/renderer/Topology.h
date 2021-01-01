#pragma once
#include <d3d11.h>
#include "Renderer.h"
#include "./Bindable.h"
#include "../core/core.h"

namespace BlitzEngine {

	class BLITZENGINE_API Topology : public Bindable
	{
	public:
		Topology(D3D_PRIMITIVE_TOPOLOGY type) noexcept :
			m_Type(type) {}

		virtual void Bind() noexcept override { Renderer::m_Context->IASetPrimitiveTopology(m_Type); }
	private:
		D3D_PRIMITIVE_TOPOLOGY m_Type;
	};

}

