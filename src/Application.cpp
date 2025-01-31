#include "Application.hpp"


Application::Application(int const width, int const height, std::string title) 
    : window(sf::VideoMode(width, height), title) {

        
}


/***********************EVENT HANDLERS******************************/



void Application::handleKeyPresses() {
    switch(e.key.code) {
        case sf::Keyboard::Key::E: {
            printf("exemple !\n");
            break;
        }

        default: break;
    }
}

void Application::handleKeyReleases() {

}

void Application::handleMouseMotion() {

}

void Application::handleMouseButtonPresses() {

}

void Application::handleMouseButtonReleases() {

}




/********************RENDER AND MAIN LOOP***************************/


void Application::update() {
    
}

void Application::render() {
    window.clear();
    

    window.display();
}


void Application::run() {
    while(window.isOpen()) {
        while(window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::EventType::Closed: {
                    window.close(); break;
                }

                case sf::Event::EventType::KeyPressed: handleKeyPresses(); break;
                case sf::Event::EventType::KeyReleased: handleKeyReleases(); break;

                case sf::Event::EventType::MouseMoved: handleMouseMotion(); break;

                case sf::Event::EventType::MouseButtonPressed: handleMouseButtonPresses(); break;
                case sf::Event::EventType::MouseButtonReleased: handleMouseButtonReleases(); break;


                default: break;
            }
        }
        update();
        render();
    }
}