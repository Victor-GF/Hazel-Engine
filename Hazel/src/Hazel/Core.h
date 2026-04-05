//
// Created by victor on 4/4/26.
//

#pragma once

#ifdef HZ_PLATFORM_WINDOWS
#ifdef HZ_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif
#elifdef HZ_PLATFORM_LINUX
#ifdef HZ_BUILD_DLL
#define HAZEL_API __attribute__((visibility("default")))
#else
#define HAZEL_API
#endif
#endif

#ifdef HZ_ENABLE_ASSERTS
    #ifdef HZ_PLATFORM_WINDOWS
        #define HZ_DEBUGBREAK() __debugbreak()
    #elif defined(HZ_PLATFORM_LINUX)
        #include <signal.h>
        #define HZ_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif

    #define HAZEL_ASSERT(x, ...) { if(!(x)) { HAZEL_ERROR("Assertion Failed: {0}", __VA_ARGS__); HZ_DEBUGBREAK(); } }
    #define HAZEL_CORE_ASSERT(x, ...) { if(!(x)) { HAZEL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HZ_DEBUGBREAK(); } }
#else
    #define HAZEL_ASSERT(x, ...)
    #define HAZEL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
