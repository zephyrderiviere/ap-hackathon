#ifndef UTILS_HPP
#define UTILS_HPP

#define LARGEUR_NIVEAU 40
#define HAUTEUR_NIVEAU 25

#define TAILLE_CASE 20

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum FileCharacters {
	WALL_CHAR = 'x',
	POTION_CHAR = 'p',
	COIN_CHAR = 'c'
};


enum MapCodes {
	NONE,
	WALL,
	POTION,
	COIN,
	PLAYER,
	ENEMY,
	ALLY,
	BULLET,
};

vector<vector<int>> lireNiveau(std::string chemin);

#endif //UTILS_HPP
