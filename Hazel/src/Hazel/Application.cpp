//
// Created by victor on 4/4/26.
//

#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/GLFW/GLFWWindow.h"

#include <glad/glad.h>

namespace Hazel
{

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

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled) break;
        }
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            glClearColor(0.3, 0.6, 0.15, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (const auto layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e)
    {
        m_IsRunning = false;
        return true;
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
    }
    void Application::PushOverlay(Layer *overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }
} // namespace Hazel
