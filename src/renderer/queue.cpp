#include "queue.hpp"

#include "logic_device.hpp"

namespace renderer {
    Queue::Queue(const LogicalDevice &logicalDevice, uint32_t queueIndex) {
        m_queue = std::make_unique<vk::raii::Queue>(logicalDevice.get(), queueIndex, 0);
    }
}
