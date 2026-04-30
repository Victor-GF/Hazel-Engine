#pragma once

#include "RendererCommand.h"

namespace Hazel
{
    class Renderer
    {
        static RendererAPI s_RendererAPI;

    public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };

} // namespace Hazel