//
// Created by victor on 4/4/26.
//

#pragma once

#include "Core.h"
#include "Window.h"

namespace Hazel
{
    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_IsRunning;
    };

    Application *CreateApplication();
} // namespace Hazel
