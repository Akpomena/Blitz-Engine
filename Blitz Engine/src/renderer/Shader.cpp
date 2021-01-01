#include "BlitzPch.h"
#include "Shader.h"
#include "Renderer.h"
#include <d3dcompiler.h>

namespace BlitzEngine {

	//Vertex Shader
	VertexShader::VertexShader(const wchar_t* shaderFile) noexcept
	{
		D3DReadFileToBlob(shaderFile, &m_VertexByteCode);
		Renderer::m_Device->CreateVertexShader(m_VertexByteCode->GetBufferPointer(), m_VertexByteCode->GetBufferSize(), nullptr, &m_VertexShader);
	}

	void VertexShader::Bind() noexcept
	{
		Renderer::m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	}

	//Pixel Shader
	PixelShader::PixelShader(const wchar_t* shaderFile) noexcept
	{
		D3DReadFileToBlob(shaderFile, &m_PixelByteCode);
		Renderer::m_Device->CreatePixelShader(m_PixelByteCode->GetBufferPointer(), m_PixelByteCode->GetBufferSize(), nullptr, &m_PixelShader);
	}

	void PixelShader::Bind() noexcept
	{
		Renderer::m_Context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}
}
