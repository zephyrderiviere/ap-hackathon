#include "Application.hpp"
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <exception>
#include "utils.hpp"


int const width = TAILLE_CASE*LARGEUR_NIVEAU;
int const height = TAILLE_CASE*HAUTEUR_NIVEAU;
std::string title = "Rogue Online";

void init(Application& app){
    // Initialize the game
    // Add a main character
    Character mainCharacter("Main", 100, 10, 5, 2, 2, 0);
    app.mainCharacter = mainCharacter;
}

int main(int argc, char** argv) { 

    int pos = std::string(argv[0]).find("bin/game");
    std::string mainDirectoryFilepath = std::string(argv[0]).substr(0, pos);

    try {
        Application app(width, height, title, "niveaux/niveau.lvl", mainDirectoryFilepath);
        init(app);
        app.run();

    } catch (std::exception e) {
        e.what();
    }

    return 0;
}
