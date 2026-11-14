#pragma once
#include <vector>

#include <vulkan/vulkan_raii.hpp>
#include "GLFW/glfw3.h"

namespace renderer {
    class Instance;
    class PhysicalDevice;
    class LogicalDevice;
    class Allocator;
    class ImageViews;

    class Renderer {
    public:
        explicit Renderer(std::vector<const char*>& required_extensions);

        ~Renderer() = default;

        void setSwapChain(VkSurfaceKHR &&surface, GLFWwindow* window);

        [[nodiscard]] const vk::raii::Instance& getInstance() const;
    private:
        std::unique_ptr<Instance> m_instance = nullptr;
        std::unique_ptr<PhysicalDevice> m_physical_device = nullptr;
        std::unique_ptr<vk::raii::SurfaceKHR> m_surface = nullptr;
        std::unique_ptr<LogicalDevice> m_device = nullptr;

        std::unique_ptr<Allocator> m_allocator = nullptr;

        vk::SurfaceFormatKHR m_format;

        std::unique_ptr<vk::raii::SwapchainKHR> m_swap_chain = nullptr;
        std::unique_ptr<ImageViews> m_image_views;

        void createSwapchain(GLFWwindow* window);
    };
}
