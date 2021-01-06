#include "BlitzPch.h"
#include "Texture2D.h"
#include "./Renderer.h"
#include "../vendor/stb_image/stb_image.h"
#include "../core/Logger.h"

namespace BlitzEngine {

	Texture2D::Texture2D(const char* path)
	{
		HRESULT result;
		int width, height, channel;
		unsigned char* data = stbi_load(path, &width, &height, &channel, 4);

		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

		if(channel != 3 && channel != 4)
			BLITZ_WARN("INVALID TEXTURE PROVIDED.. PATH: {0} :: HAS CHANNELS:: {1}", path, channel);
		

		D3D11_TEXTURE2D_DESC textureDesc = { 0 };
		textureDesc.Format = format;
		textureDesc.Height = height;
		textureDesc.Width = width;
		textureDesc.ArraySize = 1u;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.SampleDesc.Count = 1u;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.MipLevels = 1u;

		D3D11_SUBRESOURCE_DATA initialData = { 0 };
		initialData.pSysMem = data;
		initialData.SysMemPitch = width * 4;

		result = Renderer::m_Device->CreateTexture2D(&textureDesc, &initialData, &m_Texture);
		if (FAILED(result))
			BLITZ_ERROR("Failed to Create Texture");

		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));

		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		
		result = Renderer::m_Device->CreateSamplerState(&samplerDesc, &m_Sampler);
		if (FAILED(result))
			BLITZ_ERROR("Failed to Create Sampler");


		result = Renderer::m_Device->CreateShaderResourceView(m_Texture.Get(), nullptr, &m_TextureView);
		if (FAILED(result))
			BLITZ_ERROR("Failed to Create Texture View");
		
		stbi_image_free(data);
	}

	void Texture2D::Bind() noexcept
	{
		Renderer::m_Context->PSSetSamplers(0u, 1u, m_Sampler.GetAddressOf());
		Renderer::m_Context->PSSetShaderResources(0, 1, m_TextureView.GetAddressOf());
	}

}