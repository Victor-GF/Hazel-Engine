# Define os arquivos de origem
file(GLOB_RECURSE HAZEL_SOURCES "src/Hazel/*.cpp" "src/Hazel/*.h")

add_library(Hazel SHARED ${HAZEL_SOURCES})

# spdlog
set(SPDLOG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include")

# Macros
target_compile_definitions(Hazel PRIVATE HZ_BUILD_DLL)

target_include_directories(Hazel PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(Hazel PUBLIC ${SPDLOG_INCLUDE_DIR})
