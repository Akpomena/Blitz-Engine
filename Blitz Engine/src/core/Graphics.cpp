#include "BlitzPch.h"
#include "Graphics.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace BlitzEngine {

	bool Graphics::Init(HWND hwnd)
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

		Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);
		m_Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RenderTargetView);

		return true;
	}

	void Graphics::ClearScreen(float red, float green, float blue) noexcept
	{
		float color[] = { red, green, blue, 1.0f };
		m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), color);

	}

	void Graphics::DrawTriangle()
	{
		
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader = nullptr;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader = nullptr;

		Microsoft::WRL::ComPtr<ID3DBlob> pBlob = nullptr;
		HRESULT CHECK = D3DReadFileToBlob(L"../Blitz Engine/PixelShader.cso", &pBlob);
		m_Device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
		pBlob->Release();

		D3DReadFileToBlob(L"../Blitz Engine/VertexShader.cso", &pBlob);
		m_Device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout = nullptr;
		D3D11_INPUT_ELEMENT_DESC inputDesc[] = { 
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		

		m_Device->CreateInputLayout(inputDesc, 1, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer = nullptr;

		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
		};

		Vertex vertices[] = {
			DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f),
			DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f),
			DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f)
		};

		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(vertices);
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
		D3D11_SUBRESOURCE_DATA initData = { 0 };
		initData.pSysMem = vertices;

		m_Device->CreateBuffer(&bufferDesc, &initData, &pVertexBuffer);

		RECT winRect;
		GetClientRect(m_Hwnd, &winRect);
		D3D11_VIEWPORT pViewPort = {
			0.0f,
			0.0f,
			800.0f,
			600.0f,
			0.0f,
			1.0f
		};

		UINT stride = sizeof(Vertex);
		UINT offset = 0u;

		m_Context->RSSetViewports(1, &pViewPort);
		m_Context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
		m_Context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_Context->IASetInputLayout(pInputLayout.Get());
		m_Context->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_Context->VSSetShader(pVertexShader.Get(), nullptr, 0);
		m_Context->PSSetShader(pPixelShader.Get(), nullptr, 0);

		m_Context->Draw(3u, 0u);
		m_SwapChain->Present(1u, 0u);
	}

}