add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
)

target_include_directories(imgui SYSTEM PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw Vulkan::Vulkan)

add_library(Renderer::imgui ALIAS imgui)

add_library(tinygltf STATIC ${tinygltf_SOURCE_DIR}/tiny_gltf_v3.c)

target_include_directories(tinygltf SYSTEM PUBLIC ${tinygltf_SOURCE_DIR})

add_library(Renderer::tinygltf ALIAS tinygltf)


target_include_directories(renderer_vma SYSTEM INTERFACE
        ${VulkanMemoryAllocator_SOURCE_DIR}/include
)
target_link_libraries(renderer_vma INTERFACE Vulkan::Vulkan)

add_library(Renderer::vma ALIAS renderer_vma)

add_library(vulkan_settings INTERFACE)

target_compile_definitions(vulkan_settings INTERFACE
        VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
)

target_link_libraries(vulkan_settings INTERFACE Vulkan::Vulkan)

add_library(Vulkan::Settings ALIAS vulkan_settings)