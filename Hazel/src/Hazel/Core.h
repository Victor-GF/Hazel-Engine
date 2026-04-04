//
// Created by victor on 4/4/26.
//

#ifndef THECHERNO_GAMEENGINE_CORE_H
#define THECHERNO_GAMEENGINE_CORE_H

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

#endif //THECHERNO_GAMEENGINE_CORE_H
