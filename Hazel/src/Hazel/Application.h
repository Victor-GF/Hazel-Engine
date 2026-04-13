//
// Created by victor on 4/4/26.
//

#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Window.h"

#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
    class HAZEL_API Application
    {
        static Application* s_Application;
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_IsRunning;
        LayerStack m_LayerStack;

        uint32_t m_VertexArray, m_VertexBuffer, m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event &e);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);

        static Application& Get() { return *s_Application; }
        Window& GetWindow() const { return *m_Window; }
    private:
        bool OnWindowClosed(WindowCloseEvent &e);      

    };

    // To be defined on Client
    Application *CreateApplication();
} // namespace Hazel
