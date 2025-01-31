#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <map>



int main(int argc, char** argv) {
    sf::Uint16 port = 42069;

    if (argc > 1) {
        port = atoi(argv[1]);
    }

    sf::UdpSocket server;
    server.bind(port);

    bool isRunning = true;
    sf::Packet data;
    sf::Uint64 size;
    sf::IpAddress sender;
    sf::Uint16 remotePort;

    std::map<sf::IpAddress, sf::Uint8> players;
    
    sf::Vector2<float> pos;
    std::string message;
    sf::Packet p;
                

    std::string prefix = "[SERVER-INFO] ";

    sf::Uint8 nextID = 0;


    while(isRunning) {
        if (server.receive(data, sender, remotePort) == sf::Socket::Done) {
            
            
            if (data >> message) {
                std::cout << prefix << message << '\n';

                p.clear();
                if (players.find(sender) == players.end()) {
                    players.insert(std::pair(sender, nextID));

                    p << nextID;
                    nextID++;
                } else {
                    p << players.at(sender);
                }
                server.send(p, sender, port);
            }
            if (data >> pos.x >> pos.y) {
                p.clear();
                p << pos.x << pos.y;
                std::cout << prefix << '(' << pos.x << ", " << pos.y << ")\n";
                for (auto ip : players) {
                    server.send(p, ip.first, port);
                }
            }

        }
    }

    return 0;
}