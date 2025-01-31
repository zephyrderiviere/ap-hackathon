#include "Application.hpp"
#include <exception>
#include "utils.hpp"


int const width = TAILLE_CASE*LARGEUR_NIVEAU;
int const height = TAILLE_CASE*HAUTEUR_NIVEAU;
std::string title = "Rogue Online";

void init(Application& app){
    // Initialize the game
    // Add a main character
    Character mainCharacter("Main", 100, 10, 5, 0, 0);
    app.characters.push_back(mainCharacter);
}

int main(int argc, char** argv) {
    try {
        Application app(width, height, title, "niveaux/niveau.lvl");
        init(app);

        app.run();

    } catch (std::exception e) {
        e.what();
    }

    return 0;
}
