//
// Created by victor on 4/4/26.
//

#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"
#include "Hazel/Log.h"
#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        if (Hazel::Input::IsKeyPressed(HAZEL_KEY_TAB))
        HAZEL_TRACE("Tab key is pressed (poll)");
    }

    void OnEvent(Hazel::Event &event) override
    {
        if (event.GetEventType() == Hazel::EventType::KeyPressed)
        {
            auto &e = static_cast<Hazel::KeyPressedEvent &>(event);
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
        PushOverlay(new Hazel::ImGuiLayer());
    };
    ~SandboxApp() {

    };
};

Hazel::Application *Hazel::CreateApplication() { return new SandboxApp(); }
