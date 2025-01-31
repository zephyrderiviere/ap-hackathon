#include "Application.hpp"
#include "utils.hpp"
#include "Networking.hpp"
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <cstdio>
#include <iostream>
#include <stdexcept>


Application::Application(int const width, int const height, std::string title, std::string cheminNiveau, std::string& workingDirectory)
    : window(sf::VideoMode(width, height), title), workingDirectory(workingDirectory) {

    carte = lireNiveau(cheminNiveau);
}


/***********************EVENT HANDLERS******************************/



void Application::handleKeyPresses() {
    switch(e.key.code) {
        // Handle main character movement
        case sf::Keyboard::Key::Up: mainCharacter.move(carte,0,-1); break;
        case sf::Keyboard::Key::Down: mainCharacter.move(carte,0,1); break;
        case sf::Keyboard::Key::Left: mainCharacter.move(carte,-1,0); break;
        case sf::Keyboard::Key::Right: mainCharacter.move(carte,1,0); break;

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


void Application::multiPlayerMenu() {
    char address[10000];
    sf::UdpSocket socket;
    socket.setBlocking(false);
    sf::Font f;
    if (!f.loadFromFile(workingDirectory + "data/Movistar.ttf")) {
        throw std::runtime_error("Failed to load data/Movistar.ttf");
    }

    sf::Packet p;
    p << "connecting";

    for(int i=0; i<256; i++) {
        sprintf(address, "192.168.125.%d", i);

        sf::IpAddress ipAddress(lireAdresseServeur(workingDirectory));
        
        socket.send(p, ipAddress, port);
        sf::Uint16 remotePort;
        if (socket.receive(p, ipAddress, remotePort) == sf::Socket::Done) {
            //std::cout << p;
            std::cout << "!!!\n";
            sf::Text text("Remote server : " + std::string(address), f);
            text.setFillColor(sf::Color::White);
            text.setPosition((sf::Vector2f) (window.getSize() / 2u + (unsigned) i * sf::Vector2u(0, 1)));
            window.draw(text);
        }
    }
}


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
    }
}
