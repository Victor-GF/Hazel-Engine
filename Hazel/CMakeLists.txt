# Define os arquivos de origem
file(GLOB_RECURSE HAZEL_SOURCES
        "src/Hazel/*.cpp" "src/Hazel/*.h"
        "src/Hazel/Events/*.cpp" "src/Hazel/Events/*.h"
        "src/Hazel/Renderer/*.cpp" "src/Hazel/Renderer/*.h"
        "src/Hazel/ImGui/*.cpp" "src/Hazel/ImGui/*.h"
        "src/Platform/GLFW/*.cpp" "src/Platform/GLFW/*.h"
        "src/Platform/OpenGL/*.cpp" "src/Platform/OpenGL/*.h"
)

add_library(Hazel SHARED
        "src/hzpch.cpp"
        "src/hzpch.h"
        ${HAZEL_SOURCES}
)

# PCH
target_precompile_headers(Hazel PRIVATE  "src/hzpch.h")

# spdlog
set(SPDLOG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include")

# GLFW
find_package(OpenGL REQUIRED)
add_subdirectory(vendor/GLFW)

# GLAD
add_subdirectory(vendor/Glad)

# ImGui
add_subdirectory(vendor/ImGui)
target_link_libraries(ImGui PUBLIC glfw)

# GLM
add_subdirectory(vendor/glm)

# Macros
target_compile_definitions(Hazel PRIVATE
        HZ_BUILD_DLL HZ_ENABLE_ASSERTS
)
target_compile_definitions(ImGui PUBLIC
        IMGUI_IMPL_OPENGL_LOADER_GLAD
        GLFW_INCLUDE_NONE
)

target_include_directories(Hazel PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        ${SPDLOG_INCLUDE_DIR}
)

target_link_libraries(Hazel PUBLIC
        OpenGL::GL
        glfw
        Glad
        ImGui
        glm
)
