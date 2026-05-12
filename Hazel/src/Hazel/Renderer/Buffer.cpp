#include "Buffer.h"

#include "Hazel/Core.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{

    VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HAZEL_CORE_ASSERT(false, "RendererAPI::None not defined API!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }

        HAZEL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer *IndexBuffer::Create(uint32_t *vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HAZEL_CORE_ASSERT(false, "RendererAPI::None not defined API!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(vertices, size);
        }

        HAZEL_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Hazel