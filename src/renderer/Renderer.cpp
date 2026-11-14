#include "Renderer.hpp"
#include "physical_device.hpp"

namespace renderer {
    Renderer::Renderer(std::vector<const char*>& required_extensions) {
        m_instance = std::make_unique<Instance>(required_extensions);

        auto physical_device = PhysicalDevice::findPhysicalDevice(m_instance -> getPhysicalDevices());
        m_physical_device = std::make_unique<PhysicalDevice>(physical_device);
        m_device = std::make_unique<LogicalDevice>(*m_physical_device);
        m_allocator = std::make_unique<Allocator>(*m_instance, *m_physical_device, *m_device);
    }

    void Renderer::setSwapChain(VkSurfaceKHR &&surface, GLFWwindow* window) {
        m_surface = std::make_unique<vk::raii::SurfaceKHR>(m_instance -> get(), surface);

        createSwapchain(window);
    }

    void Renderer::createSwapchain(GLFWwindow* window) {
        const vk::SurfaceCapabilitiesKHR capabilities = m_physical_device -> get().getSurfaceCapabilitiesKHR(*m_surface);
        m_format = m_physical_device -> chooseFormat(*m_surface);

        vk::SwapchainCreateInfoKHR create_info{
            .surface = *m_surface,
            .minImageCount = m_physical_device -> chooseImageCount(*m_surface),
            .imageFormat = m_format.format,
            .imageColorSpace = m_format.colorSpace,
            .imageExtent = m_physical_device -> chooseExtent(*m_surface, window),
            .imageArrayLayers = 1,
            .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
            .imageSharingMode = vk::SharingMode::eExclusive,
            .queueFamilyIndexCount = m_physical_device -> getQueueIndex(),
            .preTransform = capabilities.currentTransform,
            .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
            .presentMode = m_physical_device -> choosePresentMode(*m_surface),
            .clipped = true
        };

        m_swap_chain = std::make_unique<vk::raii::SwapchainKHR>(m_device -> get(), create_info);

        m_image_views = std::make_unique<ImageViews>(*m_device, m_swap_chain -> getImages(), m_format.format);
    }
}
