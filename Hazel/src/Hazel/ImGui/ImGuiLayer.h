//
// Created by victor on 4/5/26.
//

#pragma once

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Core.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Layer.h"

namespace Hazel
{
    class HAZEL_API ImGuiLayer : public Layer
    {
        float m_DeltaTime = 0.0f;

        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
        bool OnMouseMovedEvent(MouseMovedEvent &e);
        bool OnMouseScrolledEvent(MouseScrolledEvent &e);
        bool OnKeyPressedEvent(KeyPressedEvent &e);
        bool OnKeyReleasedEvent(KeyReleasedEvent &e);
        bool OnKeyTypedEvent(KeyTypedEvent &e);
        bool OnWindowResizedEvent(WindowResizeEvent &e);

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnUpdate() override;
        void OnEvent(Event &event) override;
        void OnAttach() override;
        void OnDetach() override;
    };
} // namespace Hazel