#include "Networking.hpp"
#include <SFML/Config.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <iostream>


sf::UdpSocket* openToLAN(const sf::Uint16 port) {
    sf::UdpSocket* socket = new sf::UdpSocket();

    socket->bind(port);

    return socket;
}