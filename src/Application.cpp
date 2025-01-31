#include "Application.hpp"
#include "utils.hpp"
#include <SFML/Network.hpp>

Application::Application(int const width, int const height, std::string title, std::string cheminNiveau) 
    : window(sf::VideoMode(width, height), title) {
	carte = lireNiveau(cheminNiveau);
	serveur = lireAdresseServeur();
}


/***********************EVENT HANDLERS******************************/



void Application::handleKeyPresses() {
    switch(e.key.code) {
        // Handle main character movement
        case sf::Keyboard::Key::Up: mainCharacter.move(-1, 0); break;
        case sf::Keyboard::Key::Down: mainCharacter.move(1, 0); break;
        case sf::Keyboard::Key::Left: mainCharacter.move(0, -1); break;
        case sf::Keyboard::Key::Right: mainCharacter.move(0, 1); break;

        default: break;
    }
}

void Application::sendDataToServeur() {
	sf::UdpSocket socket;
	Position p = mainCharacter.getPosition();
	sf::Packet packet;
	packet << "connecting";

	if (socket.send(packet, serveur.ipAdresse, serveur.port) != sf::Socket::Done) {
		std::cerr << "Erreur lors de l'envoi du message." << std::endl;
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
    
    for(int i=0; i<HAUTEUR_NIVEAU; i++) {
    	for(int j=0; j<LARGEUR_NIVEAU; j++) {
    		sf::RectangleShape rectangle({TAILLE_CASE, TAILLE_CASE});
    		rectangle.setPosition(j*TAILLE_CASE, i*TAILLE_CASE);
    		rectangle.setFillColor(sf::Color::Black);
    		switch(carte[i][j]) {
    			case(WALL):
    				rectangle.setFillColor(sf::Color::Blue);
    				break;
    			case(POTION):
    				rectangle.setFillColor(sf::Color::Red);
    				break;
    			case(COIN):
    				rectangle.setFillColor(sf::Color::Yellow);
    				break;
    			case(GRAAL):
    				rectangle.setFillColor(sf::Color(100, 0, 100));
    				break;
    		}
    		window.draw(rectangle);
    	}
    }

    mainCharacter.draw(window);

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
        sendDataToServeur();
    }
}
