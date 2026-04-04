# Define os arquivos de origem
file(GLOB_RECURSE SANDBOX_SOURCES "src/*.cpp")

# Cria o executável
add_executable(Sandbox ${SANDBOX_SOURCES})

# Faz o link com a Hazel
# Isso cuida automaticamente dos includes e do link binário
target_link_libraries(Sandbox Hazel)