//
// Created by victor on 4/4/26.
//

#include "GLFWWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Log.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Hazel
{
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char *description)
    {
        HAZEL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window *Window::Create(const WindowProps &props) { return new GLFWWindow(props); }

    GLFWWindow::GLFWWindow(const WindowProps &props) { Init(props); }

    GLFWWindow::~GLFWWindow() { Shutdown(); }

    void GLFWWindow::Init(const WindowProps &props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        HAZEL_CORE_INFO("Creating GLFWWindow {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            const int success = glfwInit();
            HAZEL_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.data(), nullptr, nullptr);

        m_Context = new OpenGLContext(m_Window);
        m_Context->Init(); 

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // GLFW callbacks
        glfwSetWindowSizeCallback(m_Window,
                                  [](GLFWwindow *window, const int w, const int h)
                                  {
                                      GLFWWindowData &data =
                                          *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(window));
                                      WindowResizeEvent event(w, h);
                                      data.Width = w;
                                      data.Height = h;
                                      data.EventCallback(event);
                                  });
        glfwSetWindowCloseCallback(m_Window,
                                   [](GLFWwindow *window)
                                   {
                                       GLFWWindowData &data =
                                           *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(window));
                                       WindowCloseEvent event;
                                       data.EventCallback(event);
                                   });
        glfwSetKeyCallback(m_Window,
                           [](GLFWwindow *window, int key, int scancode, int action, int mods)
                           {
                               GLFWWindowData &data = *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(window));
                               switch (action)
                               {
                               case GLFW_PRESS:
                               {
                                   KeyPressedEvent event(key, false);
                                   data.EventCallback(event);
                                   break;
                               }
                               case GLFW_RELEASE:
                               {
                                   KeyReleasedEvent event(key);
                                   data.EventCallback(event);
                                   break;
                               }
                               case GLFW_REPEAT:
                               {
                                   KeyPressedEvent event(key, true);
                                   data.EventCallback(event);
                                   break;
                               }
                               }
                           });
        glfwSetCharCallback(m_Window,
                            [](GLFWwindow *window, unsigned int keycode)
                            {
                                GLFWWindowData &data = *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(window));

                                KeyTypedEvent event(keycode);
                                data.EventCallback(event);
                            });
        glfwSetMouseButtonCallback(m_Window,
                                   [](GLFWwindow *window, int button, int action, int mods)
                                   {
                                       auto &data =
                                           *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(window));
                                       switch (action)
                                       {
                                       case GLFW_PRESS:
                                       {
                                           MouseButtonPressedEvent event(button);
                                           data.EventCallback(event);
                                           break;
                                       }
                                       case GLFW_RELEASE:
                                       {
                                           MouseButtonReleasedEvent event(button);
                                           data.EventCallback(event);
                                           break;
                                       }
                                       }
                                   });
        glfwSetScrollCallback(m_Window,
                              [](GLFWwindow *window, double xpos, double ypos)
                              {
                                  GLFWWindowData &data =
                                      *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(window));

                                  MouseScrolledEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
                                  data.EventCallback(event);
                              });
        glfwSetCursorPosCallback(m_Window,
                                 [](GLFWwindow *window, const double xpos, const double ypos)
                                 {
                                     GLFWWindowData &data =
                                         *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(window));
                                     MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
                                     data.EventCallback(event);
                                 });
    }

    void GLFWWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void GLFWWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }
    bool GLFWWindow::IsVSync() const { return m_Data.VSync; }
    void GLFWWindow::Shutdown() { glfwDestroyWindow(m_Window); }
    //
    //     static uint8_t s_GLFWWindowCount = 0;
    //
    //     static void GLFWErrorCallback(int error, const char *description)
    //     {
    //         HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    //     }
    //
    //     WindowsWindow::WindowsWindow(const WindowProps &props)
    //     {
    //         HZ_PROFILE_FUNCTION();
    //
    //         Init(props);
    //     }
    //
    //     WindowsWindow::~WindowsWindow()
    //     {
    //         HZ_PROFILE_FUNCTION();
    //
    //         Shutdown();
    //     }
    //
    //     void WindowsWindow::Init(const WindowProps &props)
    //     {
    //         HZ_PROFILE_FUNCTION();
    //
    //         m_Data.Title = props.Title;
    //         m_Data.Width = props.Width;
    //         m_Data.Height = props.Height;
    //
    //         HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
    //
    //         if (s_GLFWWindowCount == 0)
    //         {
    //             HZ_PROFILE_SCOPE("glfwInit");
    //             int success = glfwInit();
    //             HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
    //             glfwSetErrorCallback(GLFWErrorCallback);
    //         }
    //
    //         {
    //             HZ_PROFILE_SCOPE("glfwCreateWindow");
    // #if defined(HZ_DEBUG)
    //             if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
    //                 glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    // #endif
    //             m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr,
    //             nullptr);
    //             ++s_GLFWWindowCount;
    //         }
    //
    //         m_Context = GraphicsContext::Create(m_Window);
    //         m_Context->Init();
    //
    //         glfwSetWindowUserPointer(m_Window, &m_Data);
    //         SetVSync(true);
    //
    //         // Set GLFW callbacks
    //         glfwSetWindowSizeCallback(m_Window,
    //                                   [](GLFWwindow *window, int width, int height)
    //                                   {
    //                                       WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    //                                       data.Width = width;
    //                                       data.Height = height;
    //
    //                                       WindowResizeEvent event(width, height);
    //                                       data.EventCallback(event);
    //                                   });
    //
    //         glfwSetWindowCloseCallback(m_Window,
    //                                    [](GLFWwindow *window)
    //                                    {
    //                                        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    //                                        WindowCloseEvent event;
    //                                        data.EventCallback(event);
    //                                    });
    //
    //         glfwSetKeyCallback(m_Window,
    //                            [](GLFWwindow *window, int key, int scancode, int action, int mods)
    //                            {
    //                                WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    //
    //                                switch (action)
    //                                {
    //                                case GLFW_PRESS:
    //                                {
    //                                    KeyPressedEvent event(key, 0);
    //                                    data.EventCallback(event);
    //                                    break;
    //                                }
    //                                case GLFW_RELEASE:
    //                                {
    //                                    KeyReleasedEvent event(key);
    //                                    data.EventCallback(event);
    //                                    break;
    //                                }
    //                                case GLFW_REPEAT:
    //                                {
    //                                    KeyPressedEvent event(key, true);
    //                                    data.EventCallback(event);
    //                                    break;
    //                                }
    //                                }
    //                            });
    //
    //         glfwSetCharCallback(m_Window,
    //                             [](GLFWwindow *window, unsigned int keycode)
    //                             {
    //                                 WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    //
    //                                 KeyTypedEvent event(keycode);
    //                                 data.EventCallback(event);
    //                             });
    //
    //         glfwSetMouseButtonCallback(m_Window,
    //                                    [](GLFWwindow *window, int button, int action, int mods)
    //                                    {
    //                                        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    //
    //                                        switch (action)
    //                                        {
    //                                        case GLFW_PRESS:
    //                                        {
    //                                            MouseButtonPressedEvent event(button);
    //                                            data.EventCallback(event);
    //                                            break;
    //                                        }
    //                                        case GLFW_RELEASE:
    //                                        {
    //                                            MouseButtonReleasedEvent event(button);
    //                                            data.EventCallback(event);
    //                                            break;
    //                                        }
    //                                        }
    //                                    });
    //
    //         glfwSetScrollCallback(m_Window,
    //                               [](GLFWwindow *window, double xOffset, double yOffset)
    //                               {
    //                                   WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    //
    //                                   MouseScrolledEvent event((float)xOffset, (float)yOffset);
    //                                   data.EventCallback(event);
    //                               });
    //
    //         glfwSetCursorPosCallback(m_Window,
    //                                  [](GLFWwindow *window, double xPos, double yPos)
    //                                  {
    //                                      WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    //
    //                                      MouseMovedEvent event((float)xPos, (float)yPos);
    //                                      data.EventCallback(event);
    //                                  });
    //     }
    //
    //     void WindowsWindow::Shutdown()
    //     {
    //         HZ_PROFILE_FUNCTION();
    //
    //         glfwDestroyWindow(m_Window);
    //         --s_GLFWWindowCount;
    //
    //         if (s_GLFWWindowCount == 0)
    //         {
    //             glfwTerminate();
    //         }
    //     }
    //
    //     void WindowsWindow::OnUpdate()
    //     {
    //         HZ_PROFILE_FUNCTION();
    //
    //         glfwPollEvents();
    //         m_Context->SwapBuffers();
    //     }
    //
    //     void WindowsWindow::SetVSync(bool enabled)
    //     {
    //         HZ_PROFILE_FUNCTION();
    //
    //         if (enabled)
    //             glfwSwapInterval(1);
    //         else
    //             glfwSwapInterval(0);
    //
    //         m_Data.VSync = enabled;
    //     }
    //
    //     bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

} // namespace Hazel