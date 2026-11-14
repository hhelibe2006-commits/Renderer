#include "instance.hpp"

namespace {
#if NDEBUG
    constexpr bool NDEBUG = false;
    const std::vector<const char*> required_layers{};
#else
    constexpr bool enable_validation = true;
    const std::vector required_layers{
        "VK_LAYER_KHRONOS_validation"
    };
#endif
}

namespace renderer {
    Instance::Instance(std::vector<const char*>& required_extensions) {
        m_context = std::make_unique<Context>();

        if constexpr (enable_validation) {
            required_extensions.push_back(vk::EXTDebugUtilsExtensionName);
        }

        constexpr vk::ApplicationInfo app_info = {
            .apiVersion = vk::ApiVersion14
        };

        const vk::InstanceCreateInfo create_info{
            .pApplicationInfo = &app_info,
            .enabledLayerCount = static_cast<uint32_t>(required_layers.size()),
            .ppEnabledLayerNames = required_layers.data(),
            .enabledExtensionCount = static_cast<uint32_t>(required_extensions.size()),
            .ppEnabledExtensionNames = required_extensions.data()
        };

        m_instance = std::make_unique<vk::raii::Instance>(m_context -> get(), create_info);

        m_debug_message = std::make_unique<DebugMessage>(*this);
    };

    const vk::raii::Instance& Instance::get() const {
        return *m_instance;
    }

    std::vector<vk::raii::PhysicalDevice> Instance::getPhysicalDevices() const {
        return m_instance -> enumeratePhysicalDevices();
    }
}

