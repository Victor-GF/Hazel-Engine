#pragma once

#include "Hazel/Core.h"

namespace Hazel
{

    class HAZEL_API Shader
    {
        uint32_t m_RendererID;

    public:
        Shader(const std::string_view vertexSrc, const std::string_view fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    };

} // namespace Hazel