#pragma once

#include "Hazel/Core.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
    class HAZEL_API GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}; // namespace Hazel