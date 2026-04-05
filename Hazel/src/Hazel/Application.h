//
// Created by victor on 4/4/26.
//

#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

namespace Hazel
{
    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event &e);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);

    private:
        bool OnWindowClosed(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        bool m_IsRunning;

        LayerStack m_LayerStack;
    };

    // To be defined on Client
    Application *CreateApplication();
} // namespace Hazel
