//
// Created by victor on 4/5/26.
//

#pragma once

#include "Hazel/Core.h"
#include "Hazel/Layer.h"

namespace Hazel
{
    class HAZEL_API ImGuiLayer : public Layer
    {
        float m_DeltaTime = 0.0f;

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnUpdate() override;
        void OnEvent(Event &event) override;
        void OnAttach() override;
        void OnDetach() override;
    };
} // namespace Hazel