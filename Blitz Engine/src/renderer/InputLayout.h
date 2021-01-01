#pragma once
#include "../core/Core.h"
#include "./Bindable.h"
#include <d3d11.h>
#include <wrl.h>

namespace BlitzEngine {

	class BLITZENGINE_API InputLayout : public Bindable
	{
	public:
		InputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC> layouts, ID3DBlob* bytecode) noexcept;
		virtual void Bind() noexcept override;
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	};

}

