#include "BlitzPch.h"
#include "Renderer.h"


namespace BlitzEngine {

	bool Renderer::m_Initialized = false;
	HWND Renderer::m_Hwnd = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> Renderer::m_SwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device> Renderer::m_Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Renderer::m_Context = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> Renderer::m_RenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> Renderer::m_DepthStencilView = nullptr;

	bool Renderer::Init(HWND hwnd, float width, float height)
	{
		m_Hwnd = hwnd;
		
		DXGI_MODE_DESC mDesc = { 0 };
		mDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
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

		UINT flags = 0;

#ifndef NDEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !NDEBUG

		if (FAILED(D3D11CreateDeviceAndSwapChain(
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

		Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);
		m_Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RenderTargetView);
		

		// create depth stensil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = { 0 };
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
		m_Device->CreateDepthStencilState(&dsDesc, &pDSState);

		// bind depth state
		m_Context->OMSetDepthStencilState(pDSState.Get(), 1u);

		// create depth stensil texture
		Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = 800u;
		descDepth.Height = 600u;
		descDepth.MipLevels = 1u;
		descDepth.ArraySize = 1u;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1u;
		descDepth.SampleDesc.Quality = 0u;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		m_Device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

		// create view of depth stensil texture
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0u;
		m_Device->CreateDepthStencilView(
			pDepthStencil.Get(), &descDSV, &m_DepthStencilView
		);

		// bind depth stensil and back buffer view to OM
		m_Context->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());


		D3D11_VIEWPORT viewPort = { 0 };
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MaxDepth = 1.0f;

		m_Context->RSSetViewports(1, &viewPort);

		m_Initialized = true;

		return true;
	}

	void Renderer::ShutDown() noexcept
	{
	}

	void Renderer::ClearScreen(float red, float green, float blue) noexcept
	{
		float color[] = { red, green, blue, 1.0f };
		m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), color);
		m_Context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void Renderer::SetViewPort(float width, float height)
	{

		D3D11_VIEWPORT viewPort = { 0 };
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MaxDepth = 1.0f;

		m_Context->RSSetViewports(1, &viewPort);
	}

	void Renderer::Present() noexcept
	{
		m_SwapChain->Present(1u, 0u);
	}

}