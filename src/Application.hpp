#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>




class Application {
    private:
        sf::RenderWindow window;
        sf::Event e;

        std::vector<std::vector<int>> map;


        void handleKeyPresses();
        void handleKeyReleases();
        void handleMouseMotion();
        void handleMouseButtonPresses();
        void handleMouseButtonReleases();

        void update();
        void render();

	vector<vector<int>> carte;

    public:

        Application(int const width, int const height, std::string title, std::string cheminNiveau);

        void run();
};



#endif //APPLICATION_HPP
