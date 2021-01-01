#pragma once
#include "../core/Core.h"
#include "./Bindable.h"
#include <d3d11.h>
#include <wrl.h>

namespace BlitzEngine {

	class BLITZENGINE_API VertexShader : public Bindable
	{
	public:
		VertexShader(const wchar_t* shaderFile) noexcept;
		virtual void Bind() noexcept override;
		inline ID3DBlob* GetByteCode() noexcept { return m_VertexByteCode.Get(); }
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_VertexByteCode;
	};

	class BLITZENGINE_API PixelShader : public Bindable
	{
	public:
		PixelShader(const wchar_t* shaderFile) noexcept;
		virtual void Bind() noexcept override;
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_PixelByteCode;
	};

}