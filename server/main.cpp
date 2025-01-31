#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <map>

using namespace std;

static string const prefix = "[SERVER-INFO] ";
static std::map<sf::IpAddress, std::pair<sf::Uint8, sf::Uint16>> players;

void connectPlayer() {

}

void disconnectPlayer() {

}

void sendPosition() {

}



int main(int argc, char** argv) {

    sf::Int32 nextID = 0;
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
                sf::Int32 id;
                if (players.find(sender) == players.end()) {
                    players.insert(std::pair(sender, std::pair(nextID, remotePort)));

                    id = nextID;
                } else {
                    id = players.at(sender).first;
                }
                p << id;
                std::cout << prefix << sender << " is connecting with port " << remotePort << ". Assigning ID " << id << '\n';
                server.send(p, sender, remotePort);
            }


            if (players.find(sender) == players.end()) {
                continue;
            }
            int senderID = players.at(sender).first;

            if (message == "disconnecting") {

                players.erase(sender);
                p << "Successfully disconnected !";
                server.send(p, sender, remotePort);
            
            }

            if (message == "position") {
                sf::Int32 id;
                data >> id >> pos.x >> pos.y;
                std::cout << prefix << (int) id << ", " << sender << ", " << remotePort << '\n';
                //std::cout << prefix << "Player " << senderID << " is at " <<'(' << pos.x << ", " << pos.y << ")\n";
                p << id << pos.x << pos.y;
                for (auto ip : players) {
                    server.send(p, ip.first, ip.second.second);
                }
            }

        }
    }

    return 0;
} 