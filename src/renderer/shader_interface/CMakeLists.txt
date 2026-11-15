add_library(shader_interface STATIC
        vertex.cpp
        vertex.hpp
        uniform_buffer.cpp
        uniform_buffer.hpp
)

add_library(Shader::Interface ALIAS shader_interface)

target_link_libraries(shader_interface
        PRIVATE
        glm::glm
        Vulkan::Settings
)