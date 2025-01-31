#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <map>

using namespace std;

static string const prefix = "[SERVER-INFO] ";
static sf::Uint8 nextID = 0;
static std::map<sf::IpAddress, sf::Uint8> players;

void connectPlayer() {

}

void disconnectPlayer() {

}

void sendPosition() {

}



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

    
    sf::Vector2i pos;
    std::string message;
    sf::Packet p;


    while(isRunning) {
        if (server.receive(data, sender, remotePort) == sf::Socket::Done) {
            p.clear();
            data >> message;
            
            if (message == "connecting") {
                std::cout << prefix << message << '\n';

                if (players.find(sender) == players.end()) {
                    players.insert(std::pair(sender, nextID));

                    p << nextID;
                    nextID++;
                } else {
                    p << players.at(sender);
                }
                server.send(p, sender, port);
            }


            if (players.find(sender) == players.end()) {
                continue;
            }
            int senderID = players.at(sender);

            if (message == "disconnecting") {

                players.erase(sender);
                p << "Successfully disconnected !";
                server.send(p, sender, port);
            
            }

            if (data >> pos.x >> pos.y) {

                p << pos.x << pos.y;
                std::cout << prefix << "Player " << senderID << " is at " <<'(' << pos.x << ", " << pos.y << ")\n";
                for (auto ip : players) {
                    server.send(p, ip.first, port);
                }
            }

        }
    }

    return 0;
} 