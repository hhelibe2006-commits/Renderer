#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
#undef VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

#include <vector>

#include "context.hpp"
#include "debugMessage.hpp"

namespace renderer{

    class Instance {
    public:
        explicit Instance(std::vector<const char*>& required_extensions);
        ~Instance() = default;

        [[nodiscard]] const vk::raii::Instance& get() const;

        [[nodiscard]] std::vector<vk::raii::PhysicalDevice> getPhysicalDevices() const;

    private:
        std::unique_ptr<Context> m_context = nullptr;
        std::unique_ptr<vk::raii::Instance> m_instance = nullptr;
        std::unique_ptr<DebugMessage> m_debug_message = nullptr;
    };
}
