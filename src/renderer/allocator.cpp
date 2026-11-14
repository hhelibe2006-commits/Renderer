#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#undef VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>
#undef VMA_IMPLEMENTATION

#include "allocator.hpp"

#include "instance.hpp"
#include "physical_device.hpp"

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
