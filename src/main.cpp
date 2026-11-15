#include "application.hpp"

#include <iostream>
#include <exception>

int main() {
    try {
        Application app;
        app.run();
    }catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}