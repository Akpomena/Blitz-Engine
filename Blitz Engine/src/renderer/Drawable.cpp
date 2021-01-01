#include "BlitzPch.h"
#include "Drawable.h"
#include "Renderer.h"

namespace BlitzEngine {
	
	void Drawable::Draw() noexcept
	{
		assert(m_IndexBuffer != nullptr);
		for (auto& b : m_Bindables)
		{
			b->Bind();
		}

		Renderer::m_Context->DrawIndexed(m_IndexBuffer->GetNumberOfElements(), 0u, 0);
	}

	void Drawable::AddBindable(std::unique_ptr<Bindable> b) noexcept
	{
		m_Bindables.push_back(std::move(b));
	}

	void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> b) noexcept
	{
		assert(m_IndexBuffer == nullptr);
		m_IndexBuffer = b.get();
		m_Bindables.push_back(std::move(b));
	}

}

