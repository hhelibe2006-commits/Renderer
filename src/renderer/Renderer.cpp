#include "Renderer.hpp"

#include "context.hpp"
#include "queue.hpp"
#include "physical_device.hpp"
#include "allocator.hpp"
#include "debugMessage.hpp"
#include "instance.hpp"
#include "logic_device.hpp"
#include "image_view.hpp"
#include <imgui.h>
#include <imgui_impl_vulkan.h>

namespace {
    void check_vk_result(VkResult err) {
        if (err == VK_SUCCESS) return;
        std::fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
        if (err < 0) std::abort();
    }
}

namespace renderer {
    Renderer::Renderer(std::vector<const char*>& required_extensions) {
        m_instance = std::make_unique<Instance>(required_extensions);

        auto physical_device = PhysicalDevice::findPhysicalDevice(m_instance -> getPhysicalDevices());
        m_physical_device = std::make_unique<PhysicalDevice>(physical_device);
        m_device = std::make_unique<LogicalDevice>(*m_physical_device);
        m_allocator = std::make_unique<Allocator>(*m_instance, *m_physical_device, *m_device);
    }

    Renderer::~Renderer() {
        ImGui_ImplVulkan_Shutdown();
    }

    void Renderer::draw() const {
        ImDrawData *draw = ImGui::GetDrawData();
        ImGui_ImplVulkan_RenderDrawData(draw, **m_command_buffer);
    }

    void Renderer::setSwapChain(VkSurfaceKHR &&surface, GLFWwindow* window) {
        m_surface = std::make_unique<vk::raii::SurfaceKHR>(m_instance -> get(), surface);

        createSwapchain(window);

        initImGui();
    }

    const vk::raii::Instance& Renderer::getInstance() const {
        return m_instance -> get();
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

    void Renderer::initImGui() const {
        vk::PipelineRenderingCreateInfoKHR pipline_create_info{
            .colorAttachmentCount = 1,
            .pColorAttachmentFormats = &m_format.format
        };

        ImGui_ImplVulkan_PipelineInfo imgui_pipline_info{
            .PipelineRenderingCreateInfo = pipline_create_info
        };

        ImGui_ImplVulkan_InitInfo init_info{
            .ApiVersion = vk::ApiVersion14,
            .Instance = *m_instance -> get(),
            .PhysicalDevice = *m_physical_device -> get(),
            .Device = *m_device -> get(),
            .QueueFamily = m_physical_device -> getQueueIndex(),
            .Queue = *m_device -> getQueue(),
            .DescriptorPoolSize = IMGUI_IMPL_VULKAN_MINIMUM_SAMPLED_IMAGE_POOL_SIZE
            + IMGUI_IMPL_VULKAN_MINIMUM_SAMPLER_POOL_SIZE,
            .MinImageCount = 2,
            .ImageCount = static_cast<uint32_t>(m_image_views->size()),
            .PipelineInfoMain = imgui_pipline_info,
            .UseDynamicRendering = true,
            .CheckVkResultFn = &check_vk_result
        };

        ImGui_ImplVulkan_Init(&init_info);
    }
}
