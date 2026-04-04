cmake_minimum_required(VERSION 4.2)
project(TheCherno_GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_definitions(-DHZ_PLATFORM_WINDOWS)
elseif (UNIX)
    add_definitions(-DHZ_PLATFORM_LINUX)
endif ()

add_subdirectory(Hazel)
add_subdirectory(Sandbox)
