#include "OpenGLContext.h"
#include "Hazel/Log.h"

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

        HAZEL_CORE_INFO("OpenGL Info: ");
        HAZEL_CORE_INFO("\tVendor:\t{0}", (const char*)glGetString(GL_VENDOR));
        HAZEL_CORE_INFO("\tRenderer:\t{0}", (const char*)glGetString(GL_RENDERER));
        HAZEL_CORE_INFO("\tVersion:\t{0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() { 
        glBegin(GL_TRIANGLES);
        glEnd();
        glfwSwapBuffers(m_Window); 
    }

} // namespace Hazel