#ifndef UTILS_HPP
#define UTILS_HPP

#define LARGEUR_NIVEAU 50
#define HAUTEUR_NIVEAU 15

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum FileCharacters {
	WALL_CHAR = 'x',

};


enum MapCodes {
	NONE,
	WALL,
	PLAYER,
	ENEMY,
	ALLY,
	BULLET,
};

vector<vector<int>> lireNiveau(std::string chemin);

#endif //UTILS_HPP