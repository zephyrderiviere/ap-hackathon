#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define LARGEUR_NIVEAU 50
#define HAUTEUR_NIVEAU 15

#define MUR_CARAC 'x'
#define MUR_CODE 1

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
        			case(MUR_CARAC):
        				niveau[i][j] = MUR_CODE;
        				break;
        		}
        	}
        	i++;
    	}

    	fichier.close();
    	return niveau;
}
