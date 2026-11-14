#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    class Context {
    public:
        Context();
        ~Context();

        [[nodiscard]] const vk::raii::Context& get() const;
    private:
        std::unique_ptr<vk::raii::Context> m_context;
    };
}