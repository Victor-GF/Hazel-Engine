//
// Created by victor on 4/4/26.
//

#ifndef THECHERNO_GAMEENGINE_APPLICATION_H
#define THECHERNO_GAMEENGINE_APPLICATION_H

#include "Core.h"

namespace Hazel {
    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}


#endif //THECHERNO_GAMEENGINE_APPLICATION_H
