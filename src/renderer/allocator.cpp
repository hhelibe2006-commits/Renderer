#include <vulkan/vulkan.hpp>

#include <vma/vk_mem_alloc.h>

#include "allocator.hpp"

#include "instance.hpp"
#include "physical_device.hpp"
#include "logic_device.hpp"

namespace renderer {
    Allocator::Allocator(const Instance &instance, const PhysicalDevice &physical_device, const LogicalDevice &device) {
        const VmaAllocatorCreateInfo create_info{
            .physicalDevice = *physical_device.get(),
            .device = *device.get(),
            .instance = *instance.get(),
            .vulkanApiVersion = vk::ApiVersion14
        };

        vmaCreateAllocator(&create_info, &m_allocator);
    }

    Allocator::~Allocator() {
        vmaDestroyAllocator(m_allocator);
    }
}
