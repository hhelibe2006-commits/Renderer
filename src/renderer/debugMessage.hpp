#pragma once
#include <vulkan/vulkan_raii.hpp>

#include <memory>

namespace renderer {
    class Instance;

    class DebugMessage {
    public:
        DebugMessage(const Instance& instance);
        ~DebugMessage() = default;

    private:
        std::unique_ptr<vk::raii::DebugUtilsMessengerEXT> m_debug_message;

        static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallBack(
            vk::DebugUtilsMessageSeverityFlagBitsEXT severityFlags,
            vk::DebugUtilsMessageTypeFlagsEXT type,
            const vk::DebugUtilsMessengerCallbackDataEXT* callbackFlags,
            void*);
    };
}