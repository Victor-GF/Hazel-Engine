//
// Created by victor on 4/4/26.
//

#ifndef THECHERNO_GAMEENGINE_ENTRYPOINT_H
#define THECHERNO_GAMEENGINE_ENTRYPOINT_H

#include "Application.h"

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {
    auto application = Hazel::CreateApplication();
    application->Run();
    delete application;
    return 0;
}

#endif //THECHERNO_GAMEENGINE_ENTRYPOINT_H
