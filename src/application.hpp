#pragma once
#include <memory>

#include "ui/main_window.hpp"
#include "renderer/Renderer.hpp"

class Application {
public:
    Application() = default;
    ~Application() = default;

    void run();
private:
    std::unique_ptr<ui::MainWindow> m_main_window;
    std::unique_ptr<renderer::Renderer> m_renderer;

    void initWindow();
    void initRenderer();
    void mainLoop() const;
};
