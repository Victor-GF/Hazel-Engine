//
// Created by victor on 4/4/26.
//

#include "imgui.h"
#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {
        if (Hazel::Input::IsKeyPressed(HAZEL_KEY_TAB))
            HAZEL_TRACE("Tab key is pressed (poll)");
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Teste");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

    void OnEvent(Hazel::Event &event) override
    {
        if (event.GetEventType() == Hazel::EventType::KeyPressed)
        {
            const auto &e = dynamic_cast<Hazel::KeyPressedEvent &>(event);
            if (e.GetKeyCode() == HAZEL_KEY_TAB)
                HAZEL_TRACE("Tab key is pressed (event)");
            HAZEL_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
        }
    }
};

class SandboxApp : public Hazel::Application
{
public:
    SandboxApp()
    {
        PushLayer(new ExampleLayer());
    };
    ~SandboxApp() {

    };
};

Hazel::Application *Hazel::CreateApplication() { return new SandboxApp(); }
