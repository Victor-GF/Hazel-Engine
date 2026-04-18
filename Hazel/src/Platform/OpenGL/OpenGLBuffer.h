#pragma once

#include "Hazel/Renderer/Buffer.h"
#include <cstdint>

namespace Hazel
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float *vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;

    private:
        uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;

        uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        size_t m_Count;
    };

} // namespace Hazel