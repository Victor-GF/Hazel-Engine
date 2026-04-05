//
// Created by victor on 4/4/26.
//

#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/GLFW/GLFWWindow.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
#define BIND_EVENT_FUNCTION(func)

    Application::Application()
    {
        const auto windowProps = WindowProps("Hazel", 1280, 720);
        m_Window = std::unique_ptr<Window>(Window::Create(windowProps));
        m_IsRunning = true;
        m_Window->SetEventCallback([this](Event &event) { return OnEvent(event); });
    }
    Application::~Application() {}

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent &win_close_event)
                                              { return OnWindowClosed(win_close_event); });
        HAZEL_CORE_INFO("{0}", e.ToString());
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            glClearColor(0.3, 0.6, 0.15, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e)
    {
        m_IsRunning = false;
        return true;
    }

    // To be defined on Client
    Application *CreateApplication();
} // namespace Hazel
