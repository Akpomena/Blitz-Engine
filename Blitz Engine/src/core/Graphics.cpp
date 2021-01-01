#include "BlitzPch.h"
#include "Graphics.h"
#include <d3dcompiler.h>
#include "Logger.h"
#include "../renderer/Buffer.h"
#include "../renderer/Shader.h"
#include "../renderer/Renderer.h"
#include "../renderer/InputLayout.h"
#include "../renderer/Topology.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace BlitzEngine {

	void Graphics::DrawTriangle(float x, float y, float angle)
	{
		PixelShader pixelShader(L"../Blitz Engine/PixelShader.cso");
		VertexShader vertexShader(L"../Blitz Engine/VertexShader.cso");

		InputLayout layout({ { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 } }, vertexShader.GetByteCode());

		UINT indice[] = {
		0,2,1, 2,3,1,  //Back Face
		1,3,5, 3,7,5,  //Right Face
		2,6,3, 3,6,7,  //Top Face
		4,5,7, 4,7,6,  // Front Face
		0,4,2, 2,4,6,  // Left Face
		0,1,4, 1,5,4  // Bottom Face
		};

		IndexBuffer indexBuffer(indice, sizeof(indice));

		DirectX::XMMATRIX vsConstData = DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationZ(angle) *
			DirectX::XMMatrixRotationX(angle) *
			DirectX::XMMatrixTranslation(x, y, 4.0f) *
			DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f)
		) ;

		VertexConstantBuffer vConstantBuffer(&vsConstData, sizeof(vsConstData));
		
		//Pixel Shader constant buffer

		DirectX::XMFLOAT4 vsConstData2[] = {
			DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
			DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.3f, 0.5f, 1.0f, 1.0f),
			DirectX::XMFLOAT4(0.2f, 0.7f, 0.2f, 1.0f)
		};

		PixelConstantBuffer pConstantBuffer(&vsConstData2, sizeof(vsConstData2));

		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
		};

		Vertex vertices[] = {
		DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f), //0
		DirectX::XMFLOAT3(1.0f,-1.0f,-1.0f), //1
		DirectX::XMFLOAT3(-1.0f,1.0f,-1.0f), //2
		DirectX::XMFLOAT3(1.0f,1.0f,-1.0f), //3
		DirectX::XMFLOAT3(-1.0f,-1.0f,1.0f), //4
		DirectX::XMFLOAT3(1.0f,-1.0f,1.0f), //5
		DirectX::XMFLOAT3(-1.0f,1.0f,1.0f), //6 
		DirectX::XMFLOAT3(1.0f,1.0f,1.0f) //7
		};

		VertexBuffer vertexBuffer(vertices, sizeof(vertices), 12u);
	
		Topology topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		topology.Bind();
		layout.Bind();
		vConstantBuffer.Bind();
		pConstantBuffer.Bind();
		indexBuffer.Bind();
		vertexBuffer.Bind();
		vertexShader.Bind();
		pixelShader.Bind();
		Renderer::m_Context->DrawIndexed(indexBuffer.GetNumberOfElements(), 0u, 0) ;
	}

}