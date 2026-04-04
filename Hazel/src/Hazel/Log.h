//
// Created by victor on 4/4/26.
//

#ifndef THECHERNO_GAMEENGINE_LOG_H
#define THECHERNO_GAMEENGINE_LOG_H

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Hazel
{

    class HAZEL_API Log
    {
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }
    };

} // namespace Hazel

#define HAZEL_CORE_TRACE(...)       ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HAZEL_CORE_DEBUG(...)       ::Hazel::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define HAZEL_CORE_INFO(...)        ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HAZEL_CORE_WARN(...)        ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HAZEL_CORE_ERROR(...)       ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HAZEL_CORE_FATAL(...)       ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define HAZEL_TRACE(...)       ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HAZEL_DEBUG(...)       ::Hazel::Log::GetClientLogger()->debug(__VA_ARGS__)
#define HAZEL_INFO(...)        ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HAZEL_WARN(...)        ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HAZEL_ERROR(...)       ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HAZEL_FATAL(...)       ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif // THECHERNO_GAMEENGINE_LOG_H
