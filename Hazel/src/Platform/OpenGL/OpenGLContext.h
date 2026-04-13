#pragma once

#include "Hazel/Renderer/GraphicsContext.h"


namespace Hazel
{
    class HAZEL_API OpenGLContext : public GraphicsContext
    {
        GLFWwindow* m_Window;
    public:
        OpenGLContext(GLFWwindow* window);

        void Init() override;
        void SwapBuffers() override;
    };
}; // namespace Hazel