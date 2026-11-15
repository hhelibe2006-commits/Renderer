#pragma once
#include <vulkan/vulkan_raii.hpp>

#include "GLFW/glfw3.h"

namespace renderer {
    class LogicalDevice;

    class PhysicalDevice {
    public:
        explicit PhysicalDevice(const vk::raii::PhysicalDevice& device);
        ~PhysicalDevice() = default;

        [[nodiscard]] const vk::raii::PhysicalDevice& get() const {
            return *m_physical_device;
        }

        [[nodiscard]] uint32_t getQueueFamilyIndex() const;

        [[nodiscard]] vk::SurfaceFormatKHR chooseFormat(const vk::raii::SurfaceKHR& surface) const;

        [[nodiscard]] vk::Extent2D chooseExtent(const vk::raii::SurfaceKHR& surface, GLFWwindow* window) const;

        [[nodiscard]] vk::PresentModeKHR choosePresentMode(const vk::raii::SurfaceKHR& surface) const;

        [[nodiscard]] uint32_t chooseImageCount(const vk::raii::SurfaceKHR& surface) const;

        static vk::raii::PhysicalDevice findPhysicalDevice(std::vector<vk::raii::PhysicalDevice> physical_devices);
    private:
        std::unique_ptr<vk::raii::PhysicalDevice> m_physical_device;

        uint32_t m_queue_family_index = std::numeric_limits<uint32_t>::max();

        std::unique_ptr<vk::raii::SwapchainKHR> m_swap_chain;

        [[nodiscard]] static int getScore(const vk::raii::PhysicalDevice& device);

        [[nodiscard]] static bool isDevice(const vk::raii::PhysicalDevice& device);

        void setQueueIndex();
    };
}
