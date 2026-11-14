#pragma once
#include "allocator.hpp"
#include "debugMessage.hpp"
#include "instance.hpp"
#include "physical_device.hpp"
#include "logic_device.hpp"
#include "image_view.hpp"

namespace renderer {
    class Renderer {
    public:
        explicit Renderer(std::vector<const char*>& required_extensions);

        ~Renderer() = default;

        void setSwapChain(VkSurfaceKHR &&surface, GLFWwindow* window);

        [[nodiscard]] const vk::raii::Instance& getInstance() const {
            return m_instance -> get();
        }
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
