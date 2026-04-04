//
// Created by victor on 4/4/26.
//

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel
{

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    /**
     * Description
     */
    constexpr auto LOG_PATTERN = "%^[%T] %n: %v%$";

    void Log::Init()
    {
        spdlog::set_pattern(LOG_PATTERN);

        s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("GAMEAPP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
} // namespace Hazel