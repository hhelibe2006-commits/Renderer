#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
#undef VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

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