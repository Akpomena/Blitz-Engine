#include "BlitzPch.h"
#include "Graphics.h"

#pragma comment(lib, "d3d11.lib")

namespace BlitzEngine {

	bool Graphics::Init(HWND hwnd)
	{
		DXGI_MODE_DESC mDesc;
		mDesc.Width = 0;
		mDesc.Height = 0;
		mDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		mDesc.RefreshRate.Denominator = 0;
		mDesc.RefreshRate.Numerator = 0;
		mDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		mDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC desc = { 0 };
		desc.BufferDesc = mDesc;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		desc.Flags = 0;

		UINT flags = 0;

#ifndef NDEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !NDEBUG

		if(FAILED(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_DEBUG,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&desc,
			&m_SwapChain,
			&m_Device,
			nullptr,
			&m_Context
		)))
			return false;

		ID3D11Texture2D* pBackBuffer = nullptr;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
		m_Device->CreateRenderTargetView(pBackBuffer, nullptr, &m_RenderTargetView);

		return true;
	}

	void Graphics::ClearScreen(float red, float green, float blue)
	{
		float color[] = { red, green, blue, 1.0f };
		m_Context->ClearRenderTargetView(m_RenderTargetView, color);

		m_SwapChain->Present(1u, 0u);

	}

}