#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    class LogicalDevice;

    class ImageViews {
    public:
        ImageViews(const LogicalDevice &device, std::vector<vk::Image> &&images, vk::Format format);
        ~ImageViews() = default;
    private:
        std::vector<vk::Image> m_images;
        std::vector<vk::raii::ImageView> m_image_views;
    };
}