//
// Created by victor on 4/4/26.
//

#include "Application.h"
#include "Core/TimeStep.h"
#include "GLFW/glfw3.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Core/Timestep.h"

#include <glad/glad.h>

namespace Hazel
{
    Application *Application::s_Application = nullptr;

    static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        case ShaderDataType::None:
            break;
        }

        HAZEL_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    Application::Application()
    {
        HAZEL_CORE_ASSERT(s_Application == nullptr, "Application already exists!");
        s_Application = this;

        const auto windowProps = WindowProps("Hazel", 1280, 720);
        m_Window = std::unique_ptr<Window>(Window::Create(windowProps));

        m_IsRunning = true;

        m_Window->SetEventCallback([this](Event &event) { return OnEvent(event); });

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {}

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent &win_close_event)
                                              { return OnWindowClosed(win_close_event); });

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            float time = static_cast<float>(glfwGetTime());
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (const auto layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            for (auto *layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

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
        HAZEL_CORE_ASSERT(layer != nullptr, "Layer cannot be nullptr!");

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay)
    {
        HAZEL_CORE_ASSERT(overlay, "Layer cannot be nullptr!");

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
} // namespace Hazel
