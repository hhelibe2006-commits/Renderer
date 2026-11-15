#pragma once
#include <memory>
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    class LogicalDevice;

    class CommandBuffer {
    public:
        explicit CommandBuffer(const LogicalDevice& device);
        ~CommandBuffer();

        [[nodiscard]] vk::raii::CommandBuffer &get() const {
            return *m_command_buffer;
        }
    private:
        std::unique_ptr<vk::raii::CommandPool> m_command_pool;
        std::unique_ptr<vk::raii::CommandBuffer> m_command_buffer;
    };
}
