#include "logic_device.hpp"

#include "physical_device.hpp"
#include "queue.hpp"

namespace {
    std::vector<const char*> required_extensions = {
        vk::KHRSwapchainExtensionName
    };
}

namespace renderer {
    LogicalDevice::LogicalDevice(const PhysicalDevice &physical_device) {
        float priority = 0.5;

        m_queue_family_index = physical_device.getQueueIndex();

        vk::DeviceQueueCreateInfo queue_create_info{
            .queueFamilyIndex = physical_device.getQueueIndex(),
            .queueCount = 1,
            .pQueuePriorities = &priority
        };

        vk::StructureChain<vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT> structure_chain = {
            {},
            {.shaderDrawParameters = true},
            {.dynamicRendering = true},
            {.extendedDynamicState = true}
        };

        vk::DeviceCreateInfo create_info {
            .pNext = structure_chain.get<vk::PhysicalDeviceFeatures2>(),
            .queueCreateInfoCount = 1,
            .pQueueCreateInfos = &queue_create_info,
            .enabledExtensionCount = static_cast<uint32_t>(required_extensions.size()),
            .ppEnabledExtensionNames = required_extensions.data(),
        };

        m_device = std::make_unique<vk::raii::Device>(physical_device.get(), create_info);

        m_queue = std::make_unique<Queue>(*this, physical_device.getQueueIndex());
    }

    const vk::raii::Queue& LogicalDevice::getQueue() const {
        return m_queue -> get();
    }
}
