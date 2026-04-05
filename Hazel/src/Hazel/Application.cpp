//
// Created by victor on 4/4/26.
//

#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/Windows/WinWindow.h"

#include <GLFW/glfw3.h>

namespace Hazel
{

    Application::Application()
    {
        const auto windowProps = WindowProps("Hazel", 1280, 720);
        m_Window = std::unique_ptr<Window>(Window::Create(windowProps));
        m_IsRunning = true;
    }
    Application::~Application() {}

    void Application::Run()
    {
        while (m_IsRunning)
        {
            glClearColor(0.3, 0.6, 0.15, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    // To be defined on Client
    Application *CreateApplication();
} // namespace Hazel
