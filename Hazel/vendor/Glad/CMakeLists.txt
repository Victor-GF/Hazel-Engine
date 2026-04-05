cmake_minimum_required(VERSION 3.10)
project(Glad)

set(GLAD_SOURCES
        "src/glad.c"
)

add_library(Glad STATIC ${GLAD_SOURCES})

set_target_properties(Glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(Glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC)
    set_property(TARGET Glad PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()