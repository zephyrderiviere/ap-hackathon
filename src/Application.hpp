#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "Characters.hpp"

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
        std::vector<std::vector<int>> carte;
    private:
        sf::RenderWindow window;
        sf::Event e;

        std::vector<std::vector<int>> map;

        std::string workingDirectory;


        void handleKeyPresses();
        void handleKeyReleases();
        void handleMouseMotion();
        void handleMouseButtonPresses();
        void handleMouseButtonReleases();


        void multiPlayerMenu();

        void update();
        void render();

    public:

        Application(int const width, int const height, std::string title, std::string cheminNiveau, std::string& workingDirectory);

        void run();
};



#endif //APPLICATION_HPP
