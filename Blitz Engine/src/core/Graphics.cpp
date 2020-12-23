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


		// create depth stensil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
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

		// bind depth stensil view to OM
		//m_Context->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

		return true;
	}

	void Graphics::ClearScreen(float red, float green, float blue) noexcept
	{
		float color[] = { red, green, blue, 1.0f };
		m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), color);
		//m_Context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void Graphics::DrawTriangle(float x, float y, float angle)
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
			DirectX::XMFLOAT3(-1.0f,-1.0f, -1.0f), //0
			DirectX::XMFLOAT3(1.0f,-1.0f, -1.0f), //1
			DirectX::XMFLOAT3(-1.0f,1.0f, -1.0f), //2
			DirectX::XMFLOAT3(1.0f,1.0f, -1.0f), //3
			DirectX::XMFLOAT3(-1.0f,-1.0f,1.0f), //4
			DirectX::XMFLOAT3(1.0f,-1.0f,1.0f), //5
			DirectX::XMFLOAT3(-1.0f,1.0f,1.0f), //6 
			DirectX::XMFLOAT3(1.0f,1.0f,1.0f) //7
		};

		UINT indice[] = {
		0,1,2, 2,1,3, //Back Face
		5,7,1, 7,3,1, //Right Face
		6,2,3, 6,3,7, //Top Face
		4,7,5, 4,6,7, // Front Face
		0,6,4, 0,2,6, // Left Face
		5,1,0, 0,4,5 // Bottom Face
		};

		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(vertices);
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
		D3D11_SUBRESOURCE_DATA initData = { 0 };
		initData.pSysMem = vertices;

		m_Device->CreateBuffer(&bufferDesc, &initData, &pVertexBuffer);

		Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer = nullptr;

		D3D11_BUFFER_DESC indexDesc = { 0 };
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.ByteWidth = sizeof(indice);
		

		D3D11_SUBRESOURCE_DATA initialData = { 0 };
		initialData.pSysMem = indice;

		m_Device->CreateBuffer(&indexDesc, &initialData, &pIndexBuffer);

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

		Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
		struct VS_CONSTANT_BUFFER
		{
			DirectX::XMMATRIX transform;
		};

		VS_CONSTANT_BUFFER vsConstData;
		vsConstData.transform = DirectX::XMMatrixTranspose(
			//DirectX::XMMatrixRotationY(angle) *
			DirectX::XMMatrixRotationX(angle) *
			DirectX::XMMatrixTranslation(x, y, 4.0f) *
			DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f/4.0f, 0.5f, 10.0f)
		);

		D3D11_BUFFER_DESC constDesc = { 0 };
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
		constDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constDesc.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA constInitData = { 0 };
		constInitData.pSysMem = &vsConstData;

		m_Device->CreateBuffer(&constDesc, &constInitData, &pConstantBuffer);

		m_Context->RSSetViewports(1, &pViewPort);
		m_Context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
		m_Context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_Context->IASetInputLayout(pInputLayout.Get());
		m_Context->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_Context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
		m_Context->VSSetShader(pVertexShader.Get(), nullptr, 0);
		m_Context->PSSetShader(pPixelShader.Get(), nullptr, 0);
		m_Context->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

		m_Context->DrawIndexed(std::size(indice), 0u, 0) ;
		m_SwapChain->Present(1u, 0u);
	}

}