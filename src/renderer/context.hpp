#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    class Context {
    public:
        Context();
        ~Context() = default;

        [[nodiscard]] const vk::raii::Context& get() const{
            return *m_context;
        }
    private:
        std::unique_ptr<vk::raii::Context> m_context;
    };
}