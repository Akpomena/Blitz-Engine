#pragma once
#include "../core/Core.h"
#include "./Bindable.h"
#include <d3d11.h>
#include <wrl.h>

namespace BlitzEngine {

	class BLITZENGINE_API Texture2D : public Bindable
	{
	public:
		Texture2D(const char* path);
		virtual void Bind() noexcept override;
	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	};

}