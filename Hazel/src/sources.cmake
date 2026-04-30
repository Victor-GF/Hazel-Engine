list(APPEND HAZEL_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Hazel.h" 
    "${CMAKE_CURRENT_LIST_DIR}/hzpch.h"
    "${CMAKE_CURRENT_LIST_DIR}/hzpch.cpp"
)

include("${CMAKE_CURRENT_LIST_DIR}/Hazel/sources.cmake")