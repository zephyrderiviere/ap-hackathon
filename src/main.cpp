#include "Application.hpp"


int const width = TAILLE_CASE*LARGEUR_NIVEAU;
int const height = TAILLE_CASE*HAUTEUR_NIVEAU;
std::string title = "Rogue Online";


int main(int argc, char** argv) { 

    int pos = std::string(argv[0]).find("bin/game");
    std::string mainDirectoryFilepath = std::string(argv[0]).substr(0, pos);

    try {
        Application app(width, height, title, "niveaux/niveau.lvl", mainDirectoryFilepath);
        app.run();
    } catch (std::exception e) {
        e.what();
    }



    return 0;
}
