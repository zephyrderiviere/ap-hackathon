#include "Application.hpp"
#include <exception>


int const width = 1200;
int const height = 800;
std::string title = "Rogue Online";

void init(Application& app){
    // Initialize the game
    // Add a main character
    Character mainCharacter("Main", 100, 10, 5, 0, 0);
    app.characters.push_back(mainCharacter);
}

int main(int argc, char** argv) {
    try {
        Application app(width, height, title);
        init(app);

        app.run();

    } catch (std::exception e) {
        e.what();
    }

    return 0;
}