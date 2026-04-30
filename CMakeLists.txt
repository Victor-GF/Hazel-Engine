cmake_minimum_required(VERSION 4.2)
project(TheCherno_GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_definitions(-DHZ_PLATFORM_WINDOWS)

    # Define globalmente para todos os targets criados DEPOIS desta linha
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

    add_link_options(-shared-libgcc)
elseif (UNIX)
    add_definitions(-DHZ_PLATFORM_LINUX)
endif ()

# No CMakeLists.txt principal
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Hazel)
add_subdirectory(Sandbox)
