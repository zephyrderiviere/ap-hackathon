#include "Application.hpp"
#include <exception>


int const width = 1200;
int const height = 800;
std::string title = "Rogue Online";


int main(int argc, char** argv) {
    try {
        Application app(width, height, title);

        app.run();

    } catch (std::exception e) {
        e.what();
    }

    return 0;
}