//
// Created by victor on 4/4/26.
//

#pragma once

#include "Hazel/Window.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
    class GLFWWindow : public Window
    {
    public:
        GLFWWindow(const WindowProps &props);
        ~GLFWWindow() override;

        void OnUpdate() override;

        uint32_t GetWidth() const override { return m_Data.Width; }
        uint32_t GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void *GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProps &props);
        virtual void Shutdown();

        GLFWwindow *m_Window;

        struct GLFWWindowData
        {
            std::string_view Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        GLFWWindowData m_Data;
    };

} // namespace Hazel