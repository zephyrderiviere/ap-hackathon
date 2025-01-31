#include "utils.hpp"
#include <stdexcept>

using namespace std;

vector<vector<int>> lireNiveau(std::string chemin) {

    std::ifstream fichier(chemin);
    if (!fichier) {
    	throw std::runtime_error("Erreur: Impossible d'ouvrir le fichier !");
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
        			case(POTION_CHAR):
        				niveau[i][j] = POTION;
        				break;
        			case(COIN_CHAR):
        				niveau[i][j] = COIN;
        				break;
        			case(GRAAL_CHAR):
        				niveau[i][j] = GRAAL;
        				break;
        		}
        	}
        	i++;
    	}

    	fichier.close();
    	return niveau;
}

serveurInfo lireAdresseServeur(std::string& workingDirectory) {

    	std::ifstream fichier(workingDirectory + "config.txt");
    	if (!fichier) {
    		std::cerr << "Erreur: Impossible d'ouvrir le fichier !" << std::endl;
    	}
    	
    	string adresseServeur;
    	std::getline(fichier, adresseServeur);
    	string port;
    	std::getline(fichier, port);
    	int portInt = stoi(port);

    	fichier.close();
    	
    	return {adresseServeur, portInt};
}
