#include "BlitzPch.h"
#include "Box.h"

namespace BlitzEngine {

	Box::Box(std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist) noexcept :
		r(rdist(rng)),
		droll(ddist(rng)),
		dpitch(ddist(rng)),
		dyaw(ddist(rng)),
		dphi(odist(rng)),
		dtheta(odist(rng)),
		dchi(odist(rng)),
		chi(adist(rng)),
		theta(adist(rng)),
		phi(adist(rng))
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT2 tecCoord;
		};

		Vertex vertices[] = {
			//Back Face							  
			DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f),DirectX::XMFLOAT2(0.0f, 1.0f),  //0
			DirectX::XMFLOAT3(1.0f,-1.0f,-1.0f), DirectX::XMFLOAT2(1.0f, 1.0f),  //1
			DirectX::XMFLOAT3(-1.0f,1.0f,-1.0f), DirectX::XMFLOAT2(0.0f, 0.0f),  //2
			DirectX::XMFLOAT3(1.0f,1.0f,-1.0f),  DirectX::XMFLOAT2(1.0f, 0.0f), //3
			//Right Face						
			DirectX::XMFLOAT3(1.0f,-1.0f,-1.0f), DirectX::XMFLOAT2(1.0f, 1.0f), //4
			DirectX::XMFLOAT3(1.0f,1.0f,-1.0f),  DirectX::XMFLOAT2(1.0f, 0.0f), //5
			DirectX::XMFLOAT3(1.0f,-1.0f,1.0f),  DirectX::XMFLOAT2(0.0f, 1.0f), //6
			DirectX::XMFLOAT3(1.0f,1.0f,1.0f),   DirectX::XMFLOAT2(0.0f, 0.0f), //7
			//Top Face							 
			DirectX::XMFLOAT3(-1.0f,1.0f,-1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), //8
			DirectX::XMFLOAT3(1.0f,1.0f,-1.0f),  DirectX::XMFLOAT2(1.0f, 0.0f), //9
			DirectX::XMFLOAT3(-1.0f,1.0f,1.0f),  DirectX::XMFLOAT2(0.0f, 1.0f), //10
			DirectX::XMFLOAT3(1.0f,1.0f,1.0f),   DirectX::XMFLOAT2(1.0f, 1.0f),//11
			//Front Face						
			DirectX::XMFLOAT3(-1.0f,-1.0f,1.0f), DirectX::XMFLOAT2(0.0f, 1.0f), //12
			DirectX::XMFLOAT3(1.0f,-1.0f,1.0f),  DirectX::XMFLOAT2(1.0f, 1.0f), //13
			DirectX::XMFLOAT3(-1.0f,1.0f,1.0f),  DirectX::XMFLOAT2(0.0f, 0.0f), //14
			DirectX::XMFLOAT3(1.0f,1.0f,1.0f),   DirectX::XMFLOAT2(1.0f, 0.0f), //15
			//Left Face							 
			DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f),DirectX::XMFLOAT2(0.0f, 1.0f), //16
			DirectX::XMFLOAT3(-1.0f,1.0f,-1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), //17
			DirectX::XMFLOAT3(-1.0f,-1.0f,1.0f), DirectX::XMFLOAT2(1.0f, 1.0f), //18
			DirectX::XMFLOAT3(-1.0f,1.0f,1.0f),  DirectX::XMFLOAT2(1.0f, 0.0f), //19
			//Bottom Face						
			DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f),DirectX::XMFLOAT2(0.0f, 1.0f), //20
			DirectX::XMFLOAT3(1.0f,-1.0f,-1.0f), DirectX::XMFLOAT2(1.0f, 1.0f), //21
			DirectX::XMFLOAT3(-1.0f,-1.0f,1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), //22
			DirectX::XMFLOAT3(1.0f,-1.0f,1.0f),  DirectX::XMFLOAT2(1.0f, 0.0f) //23
		};

		AddBindable(std::make_unique<VertexBuffer>(vertices, sizeof(vertices), 20u));

		auto vs = std::make_unique<VertexShader>(L"../Blitz Engine/VertexShader.cso");
		auto vsByteCode = vs->GetByteCode();
		
		AddBindable(std::move(vs));
		AddBindable(std::make_unique<PixelShader>(L"../Blitz Engine/PixelShader.cso"));

		uint16_t indice[] = {
		0,2,1, 2,3,1,  //Back Face
		4,5,6, 5,7,6,  //Right Face
		8,10,9, 9,10,11,  //Top Face
		12,13,15, 12,15,14,  // Front Face
		16,18,17, 17,18,19,  // Left Face
		20,21,22, 21,23,22  // Bottom Face
		};
		AddIndexBuffer(std::make_unique<IndexBuffer>(indice, sizeof(indice)));

		AddBindable(std::make_unique<Texture2D>("../Blitz Engine/Assets/Textures/container.jpg"));
		DirectX::XMVECTOR cb2[] =
		{
			{ 1.0f,0.0f,1.0f, 1.0f},
			{ 1.0f,0.0f,0.0f, 1.0f},
			{ 0.0f,1.0f,0.0f, 1.0f},
			{ 0.0f,0.0f,1.0f, 1.0f},
			{ 1.0f,1.0f,0.0f, 1.0f},
			{ 0.0f,1.0f,1.0f, 1.0f},
		};
		AddBindable(std::make_unique<PixelConstantBuffer>(&cb2, sizeof(cb2)));

		std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 }
		};
		
		AddBindable(std::make_unique<InputLayout>(ied, vsByteCode));

		AddBindable(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddBindable(std::make_unique<TransformConstantBuffer>(this, std::make_unique<VertexConstantBuffer>(sizeof(DirectX::XMMATRIX))));
	}

	DirectX::XMMATRIX Box::GetTransform() noexcept
	{
		return DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
			DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f) *
			DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	}

	void Box::Update(float dt) noexcept
	{
		roll += droll * dt;
		pitch += dpitch * dt;
		yaw += dyaw * dt;
		theta += dtheta * dt;
		phi += dphi * dt;
		chi += dchi * dt;
	}

}