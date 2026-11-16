#include "application.hpp"

namespace {
    constexpr std::string TITLE = "Renderer";
}

void Application::run() {
    initWindow();
    initRenderer();
    mainLoop();
}

void Application::initWindow() {
    m_main_window = std::make_unique<ui::MainWindow>(TITLE);
}

void Application::initRenderer(){
    auto required_extensions = ui::MainWindow::getRequiredExtension();
    m_renderer = std::make_unique<renderer::Renderer>(required_extensions);
    const vk::raii::Instance &instance = m_renderer -> getInstance();
    m_renderer -> setSwapChain(m_main_window -> createSurface(instance), m_main_window -> get());
}

void Application::mainLoop() const {
    while (!m_main_window -> shouldClose()) {
        m_main_window -> poolEvents();

        m_renderer -> draw();
    }
}
