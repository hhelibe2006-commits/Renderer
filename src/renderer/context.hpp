#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
#undef VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

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