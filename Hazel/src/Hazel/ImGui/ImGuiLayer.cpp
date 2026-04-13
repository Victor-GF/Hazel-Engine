//
// Created by victor on 4/5/26.
//

#include "ImGuiLayer.h"

#include "Hazel/Application.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <GLFW/glfw3.h>

namespace Hazel
{
    constexpr std::string_view ImGuiLayerName = "ImGuiLayer";

    ImGuiLayer::ImGuiLayer() : Layer(ImGuiLayerName) {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
        // ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        const auto &app = Application::Get();
        const auto window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

        HAZEL_CORE_ASSERT(window, "window cannot be nullptr!");

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        auto &io = ImGui::GetIO();
        const auto &app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            auto *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnImGuiRender()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    // MARKED TO DELETE
    // bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e)
    // {
    //     auto &io = ImGui::GetIO();
    //     io.AddMouseButtonEvent(e.GetMouseButton(), true);

    //     return false;
    // }
    // bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e)
    // {
    //     auto &io = ImGui::GetIO();
    //     io.AddMouseButtonEvent(e.GetMouseButton(), false);

    //     return false;
    // }
    // bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e)
    // {
    //     auto &io = ImGui::GetIO();
    //     io.AddMousePosEvent(e.GetX(), e.GetY());

    //     return false;
    // }
    // bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e)
    // {
    //     auto &io = ImGui::GetIO();
    //     io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());

    //     return false;
    // }
    // bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e)
    // {
    //     auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    //     auto &io = ImGui::GetIO();
    //     auto key = Hazel::ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode());

    //     io.AddKeyEvent(key, true);

    //     io.AddKeyEvent(ImGuiMod_Ctrl,
    //                    (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) || Input::IsKeyPressed(GLFW_KEY_RIGHT_CONTROL)));
    //     io.AddKeyEvent(ImGuiMod_Shift,
    //                    (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT) || Input::IsKeyPressed(GLFW_KEY_RIGHT_SHIFT)));
    //     io.AddKeyEvent(ImGuiMod_Alt,
    //                    (Input::IsKeyPressed(GLFW_KEY_LEFT_ALT) || Input::IsKeyPressed(GLFW_KEY_RIGHT_ALT)));
    //     io.AddKeyEvent(ImGuiMod_Super,
    //                    (Input::IsKeyPressed(GLFW_KEY_LEFT_SUPER) || Input::IsKeyPressed(GLFW_KEY_RIGHT_SUPER)));

    //     return false;
    // }
    // bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e)
    // {
    //     auto &io = ImGui::GetIO();
    //     auto key = Hazel::ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode());

    //     io.AddKeyEvent(key, false);

    //     return false;
    // }
    // bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent &e)
    // {
    //     auto &io = ImGui::GetIO();
    //     io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    //     io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    //     glViewport(0, 0, e.GetWidth(), e.GetHeight());

    //     return false;
    // }
    // bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e)
    // {
    //     auto &io = ImGui::GetIO();
    //     int keycode = e.GetKeyCode();
    //     io.AddInputCharacter(static_cast<unsigned short>(keycode));

    //     return false;
    // }

} // namespace Hazel
