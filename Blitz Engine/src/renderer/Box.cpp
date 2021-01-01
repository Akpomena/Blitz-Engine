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

		AddBindable(std::make_unique<VertexBuffer>(vertices, sizeof(vertices), 12u));

		auto vs = std::make_unique<VertexShader>(L"../Blitz Engine/VertexShader.cso");
		auto vsByteCode = vs->GetByteCode();
		
		AddBindable(std::move(vs));
		AddBindable(std::make_unique<PixelShader>(L"../Blitz Engine/PixelShader.cso"));

		UINT indice[] = {
		0,2,1, 2,3,1,  //Back Face
		1,3,5, 3,7,5,  //Right Face
		2,6,3, 3,6,7,  //Top Face
		4,5,7, 4,7,6,  // Front Face
		0,4,2, 2,4,6,  // Left Face
		0,1,4, 1,5,4  // Bottom Face
		};
		AddIndexBuffer(std::make_unique<IndexBuffer>(indice, sizeof(indice)));

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