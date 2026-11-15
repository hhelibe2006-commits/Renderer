#include "main_window.hpp"

#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>
#include <iostream>

#include "tab_bar.hpp"

namespace {
    constexpr int WIDTH = 800, HEIGHT = 600;

    void error_callback(int, const char* description) {
        std::cerr << description << std::endl;
    };
}

namespace ui {
    MainWindow::MainWindow(const std::string& title) {
        init();

        m_window = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), nullptr, nullptr);

        initImGui();
    }

    MainWindow::~MainWindow() {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(m_window);

        clear();
    }

    std::vector<const char *> MainWindow::getRequiredExtension() {
        uint32_t count;
        auto extensions = glfwGetRequiredInstanceExtensions(&count);

        return {extensions, extensions + count};
    }

    bool MainWindow::shouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    VkSurfaceKHR MainWindow::createSurface(const vk::raii::Instance& instance) const {
        VkSurfaceKHR _surface;

        if (glfwCreateWindowSurface(*instance, m_window, nullptr, &_surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface");
        }

        return _surface;
    }

    void MainWindow::poolEvents() {
        glfwPollEvents();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        m_tab_bar -> render();

        ImGui::Render();
    }

    void MainWindow::init() {
        glfwSetErrorCallback(error_callback);

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    }

    void MainWindow::initImGui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        m_io = &ImGui::GetIO();
        m_io -> ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui_ImplGlfw_InitForVulkan(m_window, true);

        m_tab_bar = std::make_unique<TabBar>();
    }

    void MainWindow::clear() {
        glfwTerminate();
    }
}
