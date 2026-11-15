#include "cmmand_buffer.hpp"
#include "logic_device.hpp"

namespace renderer {
    CommandBuffer::CommandBuffer(const LogicalDevice& device) {
        vk::CommandPoolCreateInfo pool_create_info{
            .flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
            .queueFamilyIndex = device.getQueueFamilyIndex(),
        };

        m_command_pool = std::make_unique<vk::raii::CommandPool>(device.get(), pool_create_info);

        vk::CommandBufferAllocateInfo pool_allocate_info{
            .commandPool = *m_command_pool,
            .level = vk::CommandBufferLevel::ePrimary,
            .commandBufferCount = 1
        };

        m_command_buffer = std::make_unique<vk::raii::CommandBuffer>(std::move(vk::raii::CommandBuffers(device.get(), pool_allocate_info).front()));
    }

    CommandBuffer::~CommandBuffer() = default;
}
