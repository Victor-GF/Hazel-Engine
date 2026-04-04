# Define os arquivos de origem
file(GLOB_RECURSE HAZEL_SOURCES "src/*.cpp" "src/*.h")

# Cria a biblioteca (no Linux gerará libHazel.so)
add_library(Hazel SHARED ${HAZEL_SOURCES})

target_compile_definitions(Hazel PRIVATE HZ_BUILD_DLL)

# Define onde os headers estão para que outros módulos os encontrem
target_include_directories(Hazel PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Define um macro para exportação (importante para portabilidade futura)
target_compile_definitions(Hazel PRIVATE HAZEL_BUILD_DLL)