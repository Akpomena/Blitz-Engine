#include "BlitzPch.h"
#include "InputLayout.h"
#include "Renderer.h"

namespace BlitzEngine {

	InputLayout::InputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC> layouts, ID3DBlob* bytecode) noexcept
	{

		Renderer::m_Device->CreateInputLayout(layouts.data(), layouts.size(), bytecode->GetBufferPointer(), bytecode->GetBufferSize(), &m_InputLayout);
	}

	void InputLayout::Bind() noexcept
	{
		Renderer::m_Context->IASetInputLayout(m_InputLayout.Get());
	}

}