#pragma once
#include "Bindable.h"
#include "./Drawable.h"

namespace BlitzEngine {

    class BLITZENGINE_API TransformConstantBuffer : public Bindable
    {
    public:
        TransformConstantBuffer(Drawable* parent, std::unique_ptr<VertexConstantBuffer> vcb) noexcept;
        virtual void Bind() noexcept override;
    private:
        Drawable* m_Parent;
        std::unique_ptr<VertexConstantBuffer> m_VCB;
    };

}