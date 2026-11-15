#pragma once
#include <imgui.h>
#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace ui {
    class TabBar;

    class MainWindow {
    public:
        explicit MainWindow(const std::string& title);
        ~MainWindow();


        [[nodiscard]] GLFWwindow* get() const {
            return m_window;
        }

        [[nodiscard]] static std::vector<const char*> getRequiredExtension() ;

        [[nodiscard]] bool shouldClose() const;

        [[nodiscard]] VkSurfaceKHR createSurface(const vk::raii::Instance& instance) const;

        void poolEvents();
    private:
        GLFWwindow *m_window;
        ImGuiIO *m_io;
        std::unique_ptr<TabBar> m_tab_bar;

        static void init();

        void initImGui();

        static void clear();
    };
}
