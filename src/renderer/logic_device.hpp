#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#undef VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

#include "queue.hpp"

namespace renderer {
    class PhysicalDevice;

    class LogicalDevice {
    public:
        explicit LogicalDevice(const PhysicalDevice& physical_device);
        ~LogicalDevice() = default;

        [[nodiscard]] const vk::raii::Queue& getQueue() const {
            return m_queue -> get();
        };

        [[nodiscard]] const vk::raii::Device& get() const {
            return *m_device;
        };
    private:
        std::unique_ptr<vk::raii::Device> m_device;
        std::unique_ptr<Queue> m_queue;

    };
}
