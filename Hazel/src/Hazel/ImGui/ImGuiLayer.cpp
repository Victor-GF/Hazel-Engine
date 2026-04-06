//
// Created by victor on 4/5/26.
//

#include "ImGuiLayer.h"

#include "GLFW/glfw3.h"
#include "Hazel/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace Hazel
{
    const std::string ImGuiLayerName = "ImGuiLayer";

    ImGuiLayer::ImGuiLayer() : Layer(ImGuiLayerName) {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO &io = ImGui::GetIO();
        const auto &application = Application::Get();
        io.DisplaySize = ImVec2(application.GetWindow().GetWidth(), application.GetWindow().GetHeight());

        const auto time = static_cast<float>(glfwGetTime());
        io.DeltaTime = m_DeltaTime > 0.0f ? (time - m_DeltaTime) : (1.0f / 60.0f);
        m_DeltaTime = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    void ImGuiLayer::OnEvent(Event &event) { Layer::OnEvent(event); }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() { Layer::OnDetach(); }
} // namespace Hazel