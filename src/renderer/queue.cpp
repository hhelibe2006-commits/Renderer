#include "queue.hpp"

#include "logic_device.hpp"

namespace renderer {
    Queue::Queue(const LogicalDevice &logicalDevice, uint32_t queueIndex) {
        m_queue = std::make_unique<vk::raii::Queue>(logicalDevice.get(), queueIndex, 0);
    }

    Queue::~Queue() = default;

    const vk::raii::Queue &Queue::get() const {
        return *m_queue;
    }

    void Queue::present(const vk::PresentInfoKHR &presentInfo) {
        vk::Result result = m_queue -> presentKHR(presentInfo);
    }
}
