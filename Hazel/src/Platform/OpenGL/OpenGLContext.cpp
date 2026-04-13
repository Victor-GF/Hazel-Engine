#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
    OpenGLContext::OpenGLContext(GLFWwindow *window) : m_Window(window) {
        HAZEL_CORE_ASSERT(window, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_Window);
        const auto gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HAZEL_CORE_ASSERT(gladStatus, "Could not initialize GLAD!");
    }

    void OpenGLContext::SwapBuffers() { 
        glBegin(GL_TRIANGLES);
        glEnd();
        glfwSwapBuffers(m_Window); 
    }

} // namespace Hazel