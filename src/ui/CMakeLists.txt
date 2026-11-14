add_library(renderer_ui STATIC
        main_window.cpp
        main_window.hpp
)
add_library(Renderer::ui ALIAS renderer_ui)

target_link_libraries(renderer_ui
        PUBLIC
        Renderer::common
        glfw
        Vulkan::Vulkan
        PRIVATE
        Renderer::warnings
)