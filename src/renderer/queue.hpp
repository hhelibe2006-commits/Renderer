#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    class LogicalDevice;

    class Queue {
    public:
        Queue(const LogicalDevice& logicalDevice, uint32_t queueIndex);
        ~Queue();

        [[nodiscard]] const vk::raii::Queue& get() const;
    private:
        std::unique_ptr<vk::raii::Queue> m_queue;
    };
}
