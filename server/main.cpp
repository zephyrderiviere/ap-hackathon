#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <iostream>



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
    while(isRunning) {
        if (server.receive(data, sender, remotePort) == sf::Socket::Done) {
            
            std::string message;
            data >> message;
            std::cout << message << '\n';
            if (message == "connecting") {
                sf::Packet p; p << "accepted";
                server.send(p, sender, remotePort);
            }
        }
    }

    return 0;
}