#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "Characters.hpp"
#include "utils.hpp"

using namespace std;

class Application {
    public:
        std::vector<Character> characters;
        Character mainCharacter;
    private:
        sf::RenderWindow window;
        sf::Event e;

        void handleKeyPresses();
        void handleKeyReleases();
        void handleMouseMotion();
        void handleMouseButtonPresses();
        void handleMouseButtonReleases();

        void update();
        void render();
        void sendDataToServeur();

	vector<vector<int>> carte;
	
	serveurInfo serveur;

    public:

        Application(int const width, int const height, std::string title, std::string cheminNiveau);

        void run();
};



#endif //APPLICATION_HPP
