#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    class LogicalDevice;

    class Queue {
    public:
        Queue(const LogicalDevice& logicalDevice, uint32_t queueIndex);
        ~Queue() = default;

        [[nodiscard]] const vk::raii::Queue& get() const {
            return *m_queue;
        }
    private:
        std::unique_ptr<vk::raii::Queue> m_queue;
    };
}
