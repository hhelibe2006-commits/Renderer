add_library(renderer_common INTERFACE)
add_library(Renderer::common ALIAS renderer_common)

target_include_directories(renderer_common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(renderer_common INTERFACE cxx_std_20)

add_subdirectory(ui)
add_subdirectory(renderer)

add_executable(Renderer
        main.cpp
        application.hpp
        application.cpp
)

target_link_libraries(Renderer PRIVATE
        Renderer::ui
        Renderer::vulkan
        Renderer::warnings
)