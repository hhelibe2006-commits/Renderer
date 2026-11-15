add_library(renderer_vulkan STATIC
        instance.cpp
        instance.hpp
        renderer.cpp
        renderer.hpp
        physical_device.cpp
        physical_device.hpp
        logic_device.cpp
        logic_device.hpp
        queue.cpp
        queue.hpp
        debugMessage.cpp
        debugMessage.hpp
        context.cpp
        context.hpp
        image_view.cpp
        image_view.hpp
        allocator.cpp
        allocator.hpp
        vma_impl.cpp
        cmmand_buffer.cpp
        cmmand_buffer.hpp
)
add_library(Renderer::vulkan ALIAS renderer_vulkan)

target_link_libraries(renderer_vulkan
        PUBLIC
        Renderer::common
        Vulkan::Settings
        GLFW::Settings
        PRIVATE
        glm::glm
        Renderer::warnings
        Renderer::imgui
)