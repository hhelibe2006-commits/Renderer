#pragma once
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
#undef VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_VULKAN

#include <string>
#include <vector>

namespace ui {
    void pollEvents();

    class MainWindow {
    public:
        explicit MainWindow(const std::string& title);
        ~MainWindow();

        [[nodiscard]] GLFWwindow* get() const {
            return m_window;
        };

        [[nodiscard]] static std::vector<const char*> getRequiredExtension() ;

        [[nodiscard]] bool shouldClose() const;

        [[nodiscard]] VkSurfaceKHR createSurface(const vk::raii::Instance& instance) const;
    private:
        GLFWwindow* m_window = nullptr;

        static void init();

        static void clear();
    };
}
