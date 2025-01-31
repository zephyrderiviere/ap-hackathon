#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#ifdef __linux__ 
    #include <SFML/Graphics.hpp>
    #include <SFML/Config.hpp>
    #include <SFML/Window/Event.hpp>
#elif _WIN32

#else 
    #error "No Valid OS"
#endif





class Application {
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



    public:

        Application(int const width, int const height, std::string title);

        void run();
};



#endif //APPLICATION_HPP