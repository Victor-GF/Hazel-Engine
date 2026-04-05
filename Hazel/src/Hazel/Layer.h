//
// Created by victor on 4/5/26.
//

#pragma once

#include "Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
    class HAZEL_API Layer
    {
    public:
        Layer(const std::string_view name);
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        const std::string_view GetName() const { return m_DebugName; }
    protected:
        std::string_view m_DebugName;
    };
} // namespace Hazel