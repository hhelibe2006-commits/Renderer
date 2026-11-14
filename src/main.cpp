#include "application.hpp"

#include <iostream>

int main() {
    try {

        Application app;
        app.run();
    }catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}