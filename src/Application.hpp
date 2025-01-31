#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Network.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "Characters.hpp"
#include "utils.hpp"

using namespace std;
enum GameState {
    MAIN_MENU,
    MULTIPLAYER_MENU,
    PLAYING,
};


class Application {
    public:
        std::vector<Character> characters;
        Character mainCharacter;

    private:
        sf::RenderWindow window;
        sf::Event e;

        std::string workingDirectory;

        sf::UdpSocket socket;
    


        void handleKeyPresses();
        void handleKeyReleases();
        void handleMouseMotion();
        void handleMouseButtonPresses();
        void handleMouseButtonReleases();


        void multiPlayerMenu();

        void update();
        void render();
        void sendDataToServeur();

	vector<vector<int>> carte;
	
	serveurInfo serveur;

    public:

        Application(int const width, int const height, std::string title, std::string cheminNiveau, std::string& workingDirectory);

        void run();
};



#endif //APPLICATION_HPP
