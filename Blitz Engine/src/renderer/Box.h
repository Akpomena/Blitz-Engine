#pragma once
#include "../core/Core.h"
#include "./Drawable.h"
#include "./BindableBase.h"

namespace BlitzEngine {

	class BLITZENGINE_API Box : public Drawable
	{
	public:
		Box(std::mt19937& rng, std::uniform_real_distribution<float>& adist,
			std::uniform_real_distribution<float>& ddist,
			std::uniform_real_distribution<float>& odist,
			std::uniform_real_distribution<float>& rdist) noexcept;

		virtual DirectX::XMMATRIX GetTransform() noexcept override;
		virtual void Update(float dt) noexcept override;
	private:
		//DirectX::XMMATRIX m_Transform;
		// positional
		float r;
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float theta;
		float phi;
		float chi;
		// speed (delta/s)
		float droll;
		float dpitch;
		float dyaw;
		float dtheta;
		float dphi;
		float dchi;
	};

}
