//
// Created by victor on 4/4/26.
//

#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Renderer/Buffer.h"

#include <glad/glad.h>

namespace Hazel
{
    Application *Application::s_Application = nullptr;

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

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[9] = {
            -0.5f, -0.5f, 0.0f, // 1
            0.0f,  0.5f,  0.0f, // 2
            0.5f,  -0.5f, 0.0f  // 3
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string_view vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main() 
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);                
            }
        )";
        std::string_view fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main() 
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (const auto layer : m_LayerStack)
            {
                layer->OnUpdate();
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
