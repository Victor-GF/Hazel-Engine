//
// Created by victor on 4/4/26.
//

#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"
#include "Hazel/Log.h"
#include "glm/ext.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "imgui.h"
#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
    {
        Rectangle();
        Triangle();
    }

    void OnAttach() override { ImGui::SetCurrentContext(Hazel::ImGuiLayer::GetContext()); }

    void OnUpdate(Hazel::Timestep ts) override
    {
        HAZEL_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

        // Rectangle
        if (Hazel::Input::IsKeyPressed(HAZEL_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        else if (Hazel::Input::IsKeyPressed(HAZEL_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        else if (Hazel::Input::IsKeyPressed(HAZEL_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        else if (Hazel::Input::IsKeyPressed(HAZEL_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;

        if (Hazel::Input::IsKeyPressed(HAZEL_KEY_A))
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        if (Hazel::Input::IsKeyPressed(HAZEL_KEY_D))
            m_CameraRotation += m_CameraRotationSpeed * ts;

        // Triangle
        if (Hazel::Input::IsKeyPressed(HAZEL_KEY_J))
            m_SquarePosition.x -= m_CameraMoveSpeed * ts;
        else if (Hazel::Input::IsKeyPressed(HAZEL_KEY_L))
            m_SquarePosition.x += m_CameraMoveSpeed * ts;

        else if (Hazel::Input::IsKeyPressed(HAZEL_KEY_I))
            m_SquarePosition.y += m_CameraMoveSpeed * ts;
        else if (Hazel::Input::IsKeyPressed(HAZEL_KEY_K))
            m_SquarePosition.y -= m_CameraMoveSpeed * ts;

        Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Hazel::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Hazel::Renderer::BeginScene(m_Camera);

        auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.06f));
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                auto transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Hazel::Renderer::Submit(m_Shader, m_VertexArray, transform);
            }
        }


        // Hazel::Renderer::Submit(m_TriangleShader, m_TriangleVertexArray);

        Hazel::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Teste");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

    void OnEvent(Hazel::Event &event) override {}

    bool OnKeyPressedEvent(Hazel::KeyPressedEvent &event) { return false; }

private:
    std::shared_ptr<Hazel::Shader> m_Shader;
    std::shared_ptr<Hazel::VertexBuffer> m_VertexBuffer;
    std::shared_ptr<Hazel::IndexBuffer> m_IndexBuffer;
    std::shared_ptr<Hazel::VertexArray> m_VertexArray;

    std::shared_ptr<Hazel::VertexArray> m_TriangleVertexArray;
    std::shared_ptr<Hazel::VertexBuffer> m_TriangleVertexBuffer;
    std::shared_ptr<Hazel::IndexBuffer> m_TriangleIndexBuffer;
    std::shared_ptr<Hazel::Shader> m_TriangleShader;

    Hazel::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    glm::vec3 m_SquarePosition;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 30.0f;

    void Rectangle()
    {
        m_VertexArray.reset(Hazel::VertexArray::Create());

        float vertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f, // 1
            -0.75f, 0.75f,  0.0f, // 2
            0.75f,  0.75f,  0.0f, // 3
            0.75f,  -0.75f, 0.0f, // 4
        };

        m_VertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

        Hazel::BufferLayout layout = {{Hazel::ShaderDataType::Float3, "a_Position"}};

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[] = {0, 1, 2, 2, 3, 0};
        m_IndexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_TriangleVertexArray.reset(Hazel::VertexArray::Create());

        std::string_view vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main() 
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);                
            }
        )";
        std::string_view fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main() 
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_Shader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));
    };
    void Triangle()
    {
        float triangleVertices[3 * 6] = {
            -0.4f, -0.4f, 0.0f, 0.7f, 0.0f, 0.7f, // Inferior Esquerdo
            0.0f,  0.4f,  0.0f, 0.0f, 0.7f, 0.0f, // Superior Central
            0.4f,  -0.4f, 0.0f, 0.7f, 0.7f, 0.7f  // Inferior Direito
        };

        m_TriangleVertexBuffer.reset(Hazel::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

        // O layout do triângulo é o mesmo (apenas posição)
        Hazel::BufferLayout layout = {{Hazel::ShaderDataType::Float3, "a_Position"},
                                      {Hazel::ShaderDataType::Float3, "a_Color"}};
        m_TriangleVertexBuffer->SetLayout(layout);
        m_TriangleVertexArray->AddVertexBuffer(m_TriangleVertexBuffer);

        // Índices para um triângulo simples (0, 1, 2)
        uint32_t triangleIndices[] = {0, 1, 2};
        m_TriangleIndexBuffer.reset(
            Hazel::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
        m_TriangleVertexArray->SetIndexBuffer(m_TriangleIndexBuffer);

        std::string_view vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec3 v_Color;

            void main() 
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);   
                v_Color = a_Color;             
            }
        )";

        std::string_view fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec3 v_Color;

            void main() 
            {
                color = vec4(v_Color, 1.0); 
            }
        )";

        m_TriangleShader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));
    };
};

class SandboxApp : public Hazel::Application
{
public:
    SandboxApp() { PushLayer(new ExampleLayer()); };
    ~SandboxApp() {

    };
};

Hazel::Application *Hazel::CreateApplication() { return new SandboxApp(); }
