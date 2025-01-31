#include "Application.hpp"
#include "Networking.hpp"

using namespace std;

Application::Application(int const width, int const height, std::string title, std::string cheminNiveau, std::string& workingDirectory)
    : window(sf::VideoMode(width, height), title), workingDirectory(workingDirectory) {
    carte = lireNiveau(cheminNiveau);

    mainCharacter = Character("Main", 100, 10, 5, 2, 2, 5);

    serveur = lireAdresseServeur(workingDirectory);
    connectToServer();
}

Application::~Application() {
    sf::Packet p;
    p << "disconnecting";
    if (socket.send(p, serveur.ipAdresse, serveur.port) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'envoi du message 2." << std::endl;
    }
}


/***********************EVENT HANDLERS******************************/


void Application::sendDataToServeur() {

    sf::Packet packet;
    packet << "position" << mainCharacter.playerID << mainCharacter.i << mainCharacter.j;
	if (socket.send(packet, serveur.ipAdresse, serveur.port) != sf::Socket::Done) {
		std::cerr << "Erreur lors de l'envoi du message 2." << std::endl;
	}

    //TODO send bullet info to server (if created)
}

void Application::connectToServer() {
	sf::Packet packet;
	packet << "connecting";

    socket.setBlocking(false);

	if (socket.send(packet, serveur.ipAdresse, serveur.port) != sf::Socket::Done) {
		std::cerr << "Erreur lors de l'envoi du message 1." << std::endl;
	}

    sf::IpAddress ip; sf::Uint16 port;
    packet.clear();
    if (socket.receive(packet, ip, port) != sf::Socket::Done) {
        throw std::runtime_error("Unable to contact server properly\n");
    }
    packet >> mainCharacter.playerID; 
    std::cout << (int) mainCharacter.playerID << '\n';


}

void Application::handleKeyPresses() {
    sendDataToServeur();
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
    sf::Packet p;
    
    sf::IpAddress sender;
    sf::Uint16 remoteport;
    socket.receive(p, sender, remoteport);
    //std::cout << sender << ", " << remoteport << '\n';

    if (sender != serveur.ipAdresse) return;
    std::string message; p >> message;
    if (message == "position") {
        sf::Int32 charID; p >> charID;
        
        sf::Vector2i charPos;
        if (p >> charPos.x >> charPos.y) {
            bool found = false;
            for (Character& c : characters) {
                if (c.playerID == charID) {
                    c.i = charPos.x; c.j = charPos.y;
                    found = true;
                }
            }
            if (!found && charID != mainCharacter.playerID) {
                characters.push_back(Character("Player" + std::to_string(charID), 100, 10, 10, charPos.x, charPos.y, 0, charID));
            }
        }
    }
    if (message == "bullet") {
        //TODO
    }
}

void Application::render() {
    window.clear();
    
    for(int i=0; i<HAUTEUR_NIVEAU; i++) {
    	for(int j=0; j<LARGEUR_NIVEAU; j++) {
    		sf::RectangleShape rectangle({TAILLE_CASE, TAILLE_CASE});
    		rectangle.setPosition(j*TAILLE_CASE, i*TAILLE_CASE);
    		if(abs((int)i-(int)mainCharacter.i) < mainCharacter.coins && abs((int)j-(int)mainCharacter.j) < mainCharacter.coins) {
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
	    	}
	    	else {
	    		rectangle.setFillColor(sf::Color(100, 100, 100));
	    	}
    		window.draw(rectangle);
    	}
    }

    for(auto character : characters) {
    	if(abs((int)character.i - (int)mainCharacter.i) < mainCharacter.coins) {
        	character.draw(window);
            carte[character.i][character.j] = NONE;
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
        window.setFramerateLimit(60);
        update();
        render();
    }
}
