#include "Application.hpp"
#include "Characters.hpp"
#include "utils.hpp"
#include "Networking.hpp"
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>


Application::Application(int const width, int const height, std::string title, std::string cheminNiveau, std::string& workingDirectory)
    : window(sf::VideoMode(width, height), title), workingDirectory(workingDirectory) {
    carte = lireNiveau(cheminNiveau);

    sf::Packet p; p << "connecting";
    socket.setBlocking(false);
    socket.send(p, "localhost", 42069);
    sf::IpAddress sender; sf::Uint16 x;
    socket.receive(p, sender, x);
    p >> x;
    std::cout << x << '\n';
    mainCharacter.playerID = x;
}


/***********************EVENT HANDLERS******************************/



void Application::handleKeyPresses() {
    switch(e.key.code) {
        // Handle main character movement
        case sf::Keyboard::Key::Up: mainCharacter.move(carte,0,-1); break;
        case sf::Keyboard::Key::Down: mainCharacter.move(carte,0,1); break;
        case sf::Keyboard::Key::Left: mainCharacter.move(carte,-1,0); break;
        case sf::Keyboard::Key::Right: mainCharacter.move(carte,1,0); break;
        // Handle main character attack
        case sf::Keyboard::Key::Space: mainCharacter.attack(carte); break;

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


void Application::multiPlayerMenu() {
    char address[10000];
    socket.setBlocking(false);
    sf::Font f;
    if (!f.loadFromFile(workingDirectory + "data/Movistar.ttf")) {
        throw std::runtime_error("Failed to load data/Movistar.ttf");
    }

    sf::Packet p;
    p << "connecting";

    for(int i=0; i<256; i++) {
        sprintf(address, "192.168.125.%d", i);

        sf::IpAddress ipAddress(lireAdresseServeur(workingDirectory).ipAdresse);
        
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

    for (auto it = mainCharacter.bullets.begin(); it != mainCharacter.bullets.end(); ) {
        int res = it->update(carte);
        if (res == -1) {
            it = mainCharacter.bullets.erase(it); // Erase the bullet and get the next iterator
        } else {
            ++it; // Move to the next bullet
    }
}

    sf::Packet p;
    p << "info" << mainCharacter.i << mainCharacter.j;

    socket.send(p, "localhost", 42069);
    
    sf::IpAddress sender;
    sf::Uint16 remoteport;
    if (socket.receive(p, sender, remoteport) == sf::Socket::Done) {
        int charID; p >> charID;
        
        sf::Vector2i charPos;
        if (p >> charPos.x >> charPos.y) {
            bool found = false;
            for (Character& c : characters) {
                if (c.playerID == charID && charID != mainCharacter.playerID) {
                    c.i = charPos.x; c.j = charPos.y;
                    found = true;
                }
            }
            if (!found) characters.push_back(Character("Player" + std::to_string(charID), 100, 10, 10, charPos.x, charPos.y, 0, charID));
        }
    }

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
    for (auto bullet : mainCharacter.bullets) {
            bullet.draw(window);
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
        sendDataToServeur();
    }
}
