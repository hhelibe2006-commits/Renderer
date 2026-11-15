#include "physical_device.hpp"

#include <map>

#include "GLFW/glfw3.h"
#include "logic_device.hpp"

namespace {
    std::vector<const char*> required_extensions{
        vk::KHRSwapchainExtensionName
    };
}

namespace renderer {
    PhysicalDevice::PhysicalDevice(const vk::raii::PhysicalDevice &device) {
        m_physical_device = std::make_unique<vk::raii::PhysicalDevice>(device);

        setQueueIndex();
    }

    uint32_t PhysicalDevice::getQueueIndex() const {
        return m_queue_family_index;
    }

    vk::SurfaceFormatKHR PhysicalDevice::chooseFormat(const vk::raii::SurfaceKHR &surface) const {
        std::vector<vk::SurfaceFormatKHR> formats = m_physical_device -> getSurfaceFormatsKHR(surface);

        auto format_ptr = std::ranges::find_if(formats, [](vk::SurfaceFormatKHR& surface) {
            return surface.format == vk::Format::eB8G8R8A8Srgb
            && surface.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
        });

        return format_ptr == formats.end() ? formats[0] : *format_ptr;
    }

    vk::Extent2D PhysicalDevice::chooseExtent(const vk::raii::SurfaceKHR &surface, GLFWwindow* window) const {
        const vk::SurfaceCapabilitiesKHR capabilities = m_physical_device -> getSurfaceCapabilitiesKHR(surface);
        if (capabilities.currentExtent.width == std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        }

        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        return {
            .width = std::clamp<uint32_t>(static_cast<uint32_t>(width), capabilities.maxImageExtent.width, capabilities.minImageExtent.width),
            .height = std::clamp<uint32_t>(static_cast<uint32_t>(height), capabilities.maxImageExtent.height, capabilities.minImageExtent.height)
        };
    }

    vk::PresentModeKHR PhysicalDevice::choosePresentMode(const vk::raii::SurfaceKHR &surface) const {
        std::vector<vk::PresentModeKHR> present_modes = m_physical_device -> getSurfacePresentModesKHR(surface);

        const auto mode_ptr = std::ranges::find_if(present_modes, [](const vk::PresentModeKHR& present_mode) {
            return present_mode == vk::PresentModeKHR::eMailbox;
        });

        return mode_ptr == present_modes.end() ? vk::PresentModeKHR::eFifo : *mode_ptr;
    }

    uint32_t PhysicalDevice::chooseImageCount(const vk::raii::SurfaceKHR &surface) const {
        const vk::SurfaceCapabilitiesKHR capabilities = m_physical_device -> getSurfaceCapabilitiesKHR(surface);

        uint32_t image_count = std::max(3u, capabilities.minImageCount);

        if (image_count > capabilities.maxImageCount && capabilities.maxImageCount != 0) {
            image_count = capabilities.maxImageCount;
        }

        return image_count;
    }

    vk::raii::PhysicalDevice PhysicalDevice::findPhysicalDevice(std::vector<vk::raii::PhysicalDevice> physical_devices) {
        std::multimap<int, vk::raii::PhysicalDevice> device_map;

        for (const auto& device : physical_devices) {
            device_map.insert(std::pair(getScore(device), device));
        }

        if (!device_map.empty() && device_map.rbegin() -> first > 0) {
            return device_map.rbegin() -> second;
        }

        throw std::runtime_error("No suitable physical Device found");
    }

    int PhysicalDevice::getScore(const vk::raii::PhysicalDevice &device) {
        if (!isDevice(device)) {
            return 0;
        }
        int score = 0;

        if (device.getProperties().deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
            score += 1000;
        }

        score += static_cast<int>(device.getProperties().limits.maxImageDimension2D);

        return score;
    }

    bool PhysicalDevice::isDevice(const vk::raii::PhysicalDevice &device) {
        const bool support_vk_version_1_3 = device.getProperties().apiVersion > vk::ApiVersion12;

        auto features = device.getFeatures2<vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT
            >();
        const bool support_features = features.get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters
        & features.get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering
        & features.get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

        std::vector<vk::QueueFamilyProperties> queue_properties = device.getQueueFamilyProperties();
        const bool support_graphics = std::ranges::any_of(queue_properties, [](const vk::QueueFamilyProperties& queue_property) {
            return static_cast<bool>(vk::QueueFlagBits::eGraphics & queue_property.queueFlags);
        });

        std::vector<vk::ExtensionProperties> extension_properties = device.enumerateDeviceExtensionProperties();
        const bool support_extensions = std::ranges::all_of(required_extensions, [&extension_properties](const char *required_extension) {
            return std::ranges::any_of(extension_properties, [&required_extension](const vk::ExtensionProperties &extension_property) {
                return strcmp(extension_property.extensionName, required_extension) == 0;
            });
        });

        return support_vk_version_1_3 && support_features && support_graphics && support_extensions;
    }

    void PhysicalDevice::setQueueIndex() {
        std::vector<vk::QueueFamilyProperties> queue_family_properties = m_physical_device -> getQueueFamilyProperties();

        for (size_t index = 0; index < queue_family_properties.size(); ++index) {
            if (queue_family_properties[index].queueFlags & vk::QueueFlagBits::eGraphics) {
                m_queue_family_index = static_cast<uint32_t>(index);
                break;
            }
        }
    }
}
