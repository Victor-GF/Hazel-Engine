#pragma once

namespace Hazel
{

    enum class RendererAPI
    {
        None = 0,
        OpenGL,
    };

    class Renderer
    {
        static RendererAPI s_RendererAPI;

    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }
    };

} // namespace Hazel