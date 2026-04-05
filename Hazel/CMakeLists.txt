# Define os arquivos de origem
file(GLOB_RECURSE HAZEL_SOURCES
        "src/Hazel/*.cpp" "src/Hazel/*.h"
        "src/Hazel/Events/*.cpp" "src/Hazel/Events/*.h"
        "src/Platform/GLFW/*.cpp" "src/Platform/GLFW/*.h"
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
add_subdirectory("vendor/GLFW")

# GLAD
add_library(Glad STATIC "vendor/Glad/src/glad.c")
set_target_properties(Glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/Glad/include")
target_include_directories(Glad PUBLIC ${GLAD_INCLUDE_DIR})

# Macros
target_compile_definitions(Hazel PRIVATE
        HZ_BUILD_DLL HZ_ENABLE_ASSERTS
        GLFW_INCLUDE_NONE)

target_include_directories(Hazel PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(Hazel PUBLIC ${SPDLOG_INCLUDE_DIR})
target_include_directories(Hazel PUBLIC ${GLAD_INCLUDE_DIR})

target_link_libraries(Hazel PUBLIC
        glfw
        OpenGL::GL
        Glad
)
