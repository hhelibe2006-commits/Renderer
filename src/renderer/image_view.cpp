#include "image_view.hpp"

#include "logic_device.hpp"

namespace renderer {
    ImageViews::ImageViews(const LogicalDevice &device, std::vector<vk::Image> &&images, vk::Format format) {
        m_images = std::move(images);
        vk::ImageViewCreateInfo create_info{
            .viewType = vk::ImageViewType::e2D,
            .format = format,
            .subresourceRange = {
                .aspectMask = vk::ImageAspectFlagBits::eColor,
                .levelCount = 1,
                .layerCount = 1,
            }
        };

        m_image_views.reserve(m_images.size());

        for (const auto& image : m_images) {
            create_info.image = image;
            m_image_views.emplace_back(device.get(), create_info);
        }
    }
}
