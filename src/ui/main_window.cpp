#include "main_window.hpp"

#include <utility>

namespace {
    constexpr int WIDTH = 800, HEIGHT = 600;

    void error_callback(int error_code, const char* description) {

    };
}

namespace ui {
    void pollEvents() {
        glfwPollEvents();
    }

    MainWindow::MainWindow(const std::string& title) {
        init();

        m_window = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), nullptr, nullptr);
    }

    MainWindow::~MainWindow() {
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

    void MainWindow::init() {
        glfwSetErrorCallback(error_callback);

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    }

    void MainWindow::clear() {
        glfwTerminate();
    }
}
