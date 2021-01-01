#include "BlitzPch.h"
#include "Buffer.h"
#include "../renderer/Renderer.h"

namespace BlitzEngine {

	//Vertex Buffer
	VertexBuffer::VertexBuffer(void* buffer, uint32_t size, uint32_t stride) noexcept :
		m_Stride(stride)
	{ 

		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = size;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
 
		D3D11_SUBRESOURCE_DATA initData = { 0 };
		initData.pSysMem = buffer;

		Renderer::m_Device->CreateBuffer(&bufferDesc, &initData, &m_VertexBuffer);

	}

	void VertexBuffer::Bind() noexcept
	{
		constexpr UINT offset = 0u;

		Renderer::m_Context->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &m_Stride, &offset);

	}



	//Index Buffer
	IndexBuffer::IndexBuffer(UINT* indices, uint32_t size) noexcept
	{
		D3D11_BUFFER_DESC indexDesc = { 0 };
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.ByteWidth = size;


		D3D11_SUBRESOURCE_DATA initialData = { 0 };
		initialData.pSysMem = indices;

		Renderer::m_Device->CreateBuffer(&indexDesc, &initialData, &m_IndexBuffer);

		m_NumberOfElements = size / sizeof(UINT);

	}

	void IndexBuffer::Bind() noexcept
	{
		Renderer::m_Context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	}



	//Vertex Constant Buffer
	VertexConstantBuffer::VertexConstantBuffer(void* buffer, uint32_t size) noexcept
	{
		D3D11_BUFFER_DESC constDesc = { 0 };
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = size;
		constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constDesc.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA constInitData = { 0 };
		constInitData.pSysMem = buffer;

		Renderer::m_Device->CreateBuffer(&constDesc, &constInitData, &m_VertexConstantBuffer);
	}

	VertexConstantBuffer::VertexConstantBuffer(uint32_t size) noexcept
	{
		D3D11_BUFFER_DESC constDesc = { 0 };
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = size;
		constDesc.CPUAccessFlags = 0;
		constDesc.Usage = D3D11_USAGE_DEFAULT;

		HRESULT check = Renderer::m_Device->CreateBuffer(&constDesc, nullptr, &m_VertexConstantBuffer);
	}

	void VertexConstantBuffer::Bind() noexcept
	{
		Renderer::m_Context->VSSetConstantBuffers(0u, 1u, m_VertexConstantBuffer.GetAddressOf());
	}



	//Pixel Constant Buffer
	PixelConstantBuffer::PixelConstantBuffer(void* buffer, uint32_t size) noexcept
	{
		D3D11_BUFFER_DESC constDesc = { 0 };
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = size;
		constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constDesc.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA constInitData = { 0 };
		constInitData.pSysMem = buffer;

		Renderer::m_Device->CreateBuffer(&constDesc, &constInitData, &m_PixelConstantBuffer);
	}

	void PixelConstantBuffer::Bind() noexcept
	{
		Renderer::m_Context->PSSetConstantBuffers(0u, 1u, m_PixelConstantBuffer.GetAddressOf());
	}

}

