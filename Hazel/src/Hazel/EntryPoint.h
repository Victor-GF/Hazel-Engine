//
// Created by victor on 4/4/26.
//

#ifndef THECHERNO_GAMEENGINE_ENTRYPOINT_H
#define THECHERNO_GAMEENGINE_ENTRYPOINT_H

#include "Application.h"
#include "Log.h"

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char **argv)
{
    Hazel::Log::Init();
    HAZEL_CORE_WARN("Initialized Core Logger");
    HAZEL_WARN("Initialized Client Logger");

    HAZEL_INFO("Hello World! Today is {0}", 4);

    auto application = Hazel::CreateApplication();
    application->Run();
    delete application;
    return 0;
}

#endif // THECHERNO_GAMEENGINE_ENTRYPOINT_H
