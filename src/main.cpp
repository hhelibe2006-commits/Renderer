#include "application.hpp"

#include <iostream>
#include <exception>

int main() {
    try {
        Application app;
        app.run();
    } catch (vk::Error& e) {
        std::cerr << "Vulkan error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}