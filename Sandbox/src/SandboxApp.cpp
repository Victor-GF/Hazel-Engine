//
// Created by victor on 4/4/26.
//

#include <Hazel.h>

class SandboxApp : public Hazel::Application {
public:
    SandboxApp() = default;
    ~SandboxApp() = default;
};

Hazel::Application* Hazel::CreateApplication() {
    return new SandboxApp();
}
