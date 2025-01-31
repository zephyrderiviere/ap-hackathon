#include "Application.hpp"
#include "utils.hpp"

Application::Application(int const width, int const height, std::string title, std::string cheminNiveau) 
    : window(sf::VideoMode(width, height), title) {
	carte = lireNiveau(cheminNiveau);
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
    // Loop over characters and draw them
    for(auto& c : characters) {
        c.draw(window);
    }
    
    for(int i=0; i<HAUTEUR_NIVEAU; i++) {
    	for(int j=0; j<LARGEUR_NIVEAU; j++) {
    		switch(carte[i][j]) {
    			case(WALL):
    				sf::RectangleShape rectangle({TAILLE_CASE, TAILLE_CASE});
    				rectangle.setPosition(j*TAILLE_CASE, i*TAILLE_CASE);
    				rectangle.setFillColor(sf::Color::Blue);
    				window.draw(rectangle);
    				break;
    		}
    	}
    }

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
