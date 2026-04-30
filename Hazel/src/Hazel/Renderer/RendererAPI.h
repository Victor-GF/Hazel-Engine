#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include <memory>

namespace Hazel
{

    class HAZEL_API RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL,
        };

    private:
        static API s_API;

    public:

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

        constexpr static API GetAPI() { return s_API; }
    };
} // namespace Hazel