#include "Application.hpp"
#include <exception>
#include "utils.hpp"


int const width = TAILLE_CASE*LARGEUR_NIVEAU;
int const height = TAILLE_CASE*HAUTEUR_NIVEAU;
std::string title = "Rogue Online";


int main(int argc, char** argv) {
    try {
        Application app(width, height, title, "niveaux/niveau.lvl");

        app.run();

    } catch (std::exception e) {
        e.what();
    }

    return 0;
}
