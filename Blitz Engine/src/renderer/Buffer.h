#pragma once
#include "../core/Core.h"
#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "./Bindable.h"

namespace BlitzEngine {

	//VERTEX BUFFER
	class BLITZENGINE_API VertexBuffer : public Bindable
	{
	public:
		VertexBuffer(void* buffer, uint32_t size, uint32_t stride) noexcept;
		virtual void Bind() noexcept override;
	private:
		uint32_t m_Stride;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer = nullptr;
	};


	//INDEX BUFFER
	class BLITZENGINE_API IndexBuffer : public Bindable
	{
	public:
		IndexBuffer(UINT* indices, uint32_t size) noexcept;
		inline const UINT& GetNumberOfElements() const { return m_NumberOfElements; }
		virtual void Bind() noexcept override;
	private:
		UINT m_NumberOfElements;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
	};


	//VERTEXCONSTANT BUFFER
	class BLITZENGINE_API VertexConstantBuffer : public Bindable
	{
	public:
		VertexConstantBuffer(void* buffer, uint32_t size) noexcept;
		VertexConstantBuffer(uint32_t size) noexcept;
		virtual void Bind() noexcept override;
	public:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexConstantBuffer;
	};


	//PIXELCONSTANTBUFFER
	class BLITZENGINE_API PixelConstantBuffer : public Bindable
	{
	public:
		PixelConstantBuffer(void* buffer, uint32_t size) noexcept;
		virtual void Bind() noexcept override;
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_PixelConstantBuffer;
	};

}

