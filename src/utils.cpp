#include "utils.hpp"

using namespace std;


vector<vector<int>> lireNiveau(std::string chemin) {

    std::ifstream fichier(chemin);
    if (!fichier) {
    	std::cerr << "Erreur: Impossible d'ouvrir le fichier !" << std::endl;
    }

	vector<vector<int>> niveau(HAUTEUR_NIVEAU, vector<int> (LARGEUR_NIVEAU));

    	std::string ligne;
    	int i = 0;
    	while (std::getline(fichier, ligne)) {
        	for(int j=0; j<LARGEUR_NIVEAU; j++) {
        		switch(ligne[j]) {
        			case(WALL_CHAR):
        				niveau[i][j] = WALL;
        				break;
        		}
        	}
        	i++;
    	}

    	fichier.close();
    	return niveau;
}
