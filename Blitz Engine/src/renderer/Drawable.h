#pragma once
#include "../core/Core.h"
#include "./Buffer.h"

namespace BlitzEngine {

	class BLITZENGINE_API Drawable
	{
	public:
		Drawable() = default;
		Drawable(const Drawable&) = delete;
		Drawable& operator=(const Drawable&) = delete;
		virtual void Draw() noexcept;
		virtual void AddBindable(std::unique_ptr<Bindable> b) noexcept;
		virtual void AddIndexBuffer(std::unique_ptr<IndexBuffer> b) noexcept;
		virtual void Update(float dt) noexcept = 0;
		virtual DirectX::XMMATRIX GetTransform() noexcept = 0;
		virtual ~Drawable() = default;
	private:
		std::vector<std::unique_ptr<Bindable>> m_Bindables;
		const IndexBuffer* m_IndexBuffer = nullptr;
	};

}