#include "debugMessage.hpp"

#include <iostream>

#include "instance.hpp"

namespace renderer {
    DebugMessage::DebugMessage(const Instance &instance) {
        vk::DebugUtilsMessengerCreateInfoEXT create_info{
            .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
            | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
            .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
            | vk::DebugUtilsMessageTypeFlagBitsEXT::eDeviceAddressBinding
            | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            .pfnUserCallback = &debugCallBack
        };

        m_debug_message = std::make_unique<vk::raii::DebugUtilsMessengerEXT>(instance.get(), create_info);
    }

    vk::Bool32 DebugMessage::debugCallBack(
        vk::DebugUtilsMessageSeverityFlagBitsEXT,
        const vk::DebugUtilsMessageTypeFlagsEXT type,
        const vk::DebugUtilsMessengerCallbackDataEXT *callbackFlags,
        void *) {
        std::cerr << "validation layer: type " << to_string(type) << " msg: " << callbackFlags->pMessage <<std::endl;

        return vk::False;
    }
}
