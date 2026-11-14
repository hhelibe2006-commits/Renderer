#pragma once

#include <vma/vk_mem_alloc.h>

namespace renderer {
    class PhysicalDevice;
    class LogicalDevice;
    class Instance;

    class Allocator {
    public:
        Allocator(const Instance &instance,const PhysicalDevice &physical_device, const LogicalDevice &device);
        ~Allocator();

    private:
        VmaAllocator m_allocator = nullptr;
    };
}
