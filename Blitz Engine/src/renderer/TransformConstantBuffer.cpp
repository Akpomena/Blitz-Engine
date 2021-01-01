#include "BlitzPch.h"
#include "TransformConstantBuffer.h"
#include "./Renderer.h"

namespace BlitzEngine {

	TransformConstantBuffer::TransformConstantBuffer(Drawable* parent, std::unique_ptr<VertexConstantBuffer> vcb) noexcept :
		m_Parent(parent), m_VCB(std::move(vcb))
	{
	}

	void TransformConstantBuffer::Bind() noexcept
	{
		Renderer::m_Context->UpdateSubresource(m_VCB->m_VertexConstantBuffer.Get(), 0, 0, &m_Parent->GetTransform(), 0, 0);
		m_VCB->Bind();
	}

}