add_library(renderer_ui STATIC
        main_window.cpp
        main_window.hpp
        tab_bar.cpp
        tab_bar.hpp
)
add_library(Renderer::ui ALIAS renderer_ui)

target_link_libraries(renderer_ui
        PUBLIC
        Renderer::common
        GLFW::Settings
        Vulkan::Settings
        Renderer::imgui
        PRIVATE
        Renderer::warnings
)