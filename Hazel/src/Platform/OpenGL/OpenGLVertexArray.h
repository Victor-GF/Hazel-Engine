#pragma once

#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
    class HAZEL_API OpenGLVertexArray : public VertexArray
    {
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        uint32_t m_RenderID;

    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() noexcept override
        {
            return m_VertexBuffers;
        };
        std::shared_ptr<IndexBuffer> &GetIndexBuffer() noexcept override { return m_IndexBuffer; };
    };
} // namespace Hazel