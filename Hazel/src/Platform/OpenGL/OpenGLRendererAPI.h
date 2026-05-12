#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{

    class HAZEL_API OpenGLRendererAPI : public RendererAPI
    {
    public:
        OpenGLRendererAPI() {};
        ~OpenGLRendererAPI() {};

        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;

        void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

} // namespace Hazel