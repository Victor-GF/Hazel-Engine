#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {

    VertexArray *VertexArray::Create() {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HAZEL_CORE_ASSERT(false, "RendererAPI::None not defined API!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexArray();
        }

        HAZEL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}