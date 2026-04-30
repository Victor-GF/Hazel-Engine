//
// Created by victor on 4/4/26.
//

#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include <cstdint>
#include <glad/glad.h>
#include <vector>

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

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f, 
            0.0f,  0.5f,  0.0f, 
            0.5f,  -0.5f, 0.0f, 
            -0.5f,  0.5f, 0.0f, 
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float4, "a_Color"}};

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        std::string_view vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            //layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            //out vec4 v_Color;

            void main() 
            {
                v_Position = a_Position;
                //v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);                
            }
        )";
        std::string_view fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            //in vec4 v_Color;

            void main() 
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
                //color = v_Color;
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
            m_VertexArray->Bind();
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
