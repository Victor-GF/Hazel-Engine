//
// Created by victor on 4/4/26.
//

#pragma once

#include "Events/Event.h"

namespace Hazel
{

    struct WindowProps
    {
        std::string_view Title;
        uint32_t Width;
        uint32_t Height;

        explicit WindowProps(const std::string_view title, const uint32_t width, const uint32_t height)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class HAZEL_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void *GetNativeWindow() const = 0;

        static Window *Create(const WindowProps &props);
    };

} // namespace Hazel