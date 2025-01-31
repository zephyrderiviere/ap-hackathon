#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Window/Event.hpp>
#ifdef __linux__ 
    #include <SFML/Graphics.hpp>
#elif _WIN32

#else 
    #error "No Valid OS"
#endif





class Application {
    private:
        sf::RenderWindow window;
        sf::Event e;

        void render();

        void handleKeyPresses();
        void handleKeyReleases();
        void handleMouseMotion();
        void handleMouseButtonPresses();
        void handleMouseButtonReleases();



    public:

        
        Application(int const width, int const height, std::string title);


        void run();


};



#endif //APPLICATION_HPP