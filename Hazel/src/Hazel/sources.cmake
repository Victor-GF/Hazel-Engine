list( APPEND HAZEL_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Events/ApplicationEvent.h"
    "${CMAKE_CURRENT_LIST_DIR}/Events/Event.h"
    "${CMAKE_CURRENT_LIST_DIR}/Events/KeyEvent.h"
    "${CMAKE_CURRENT_LIST_DIR}/Events/MouseEvent.h"
    "${CMAKE_CURRENT_LIST_DIR}/ImGui/ImGuiBuild.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ImGui/ImGuiLayer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ImGui/ImGuiLayer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Application.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Application.h"
    "${CMAKE_CURRENT_LIST_DIR}/Core.h"
    "${CMAKE_CURRENT_LIST_DIR}/EntryPoint.h"
    "${CMAKE_CURRENT_LIST_DIR}/Input.h"
    "${CMAKE_CURRENT_LIST_DIR}/KeyCodes.h"
    "${CMAKE_CURRENT_LIST_DIR}/Layer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Layer.h"
    "${CMAKE_CURRENT_LIST_DIR}/LayerStack.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/LayerStack.h"
    "${CMAKE_CURRENT_LIST_DIR}/Log.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Log.h"
    "${CMAKE_CURRENT_LIST_DIR}/MouseButtonCodes.h"
    "${CMAKE_CURRENT_LIST_DIR}/Window.h"
)

include("${CMAKE_CURRENT_LIST_DIR}/Events/sources.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ImGui/sources.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Renderer/sources.cmake")