#include "Networking.hpp"


sf::UdpSocket* openToLAN(const sf::Uint16 port) {
    sf::UdpSocket* socket = new sf::UdpSocket();

    socket->bind(port);

    return socket;
}