//
// Created by victor on 4/4/26.
//

#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        HAZEL_INFO("ExampleLayer::OnUpdate");
    }
    void OnEvent(Hazel::Event &event) override
    {
        HAZEL_TRACE("{0}", event.ToString());
    }
};

class SandboxApp : public Hazel::Application
{
public:
    SandboxApp()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Hazel::ImGuiLayer());
    };
    ~SandboxApp()
    {

    };
};

Hazel::Application *Hazel::CreateApplication() { return new SandboxApp(); }
