#ifndef NETWORKING_HPP
#define NETWORKING_HPP

#include <SFML/Network.hpp>


sf::UdpSocket* openToLAN(const sf::Uint16);

static sf::Uint16 const port = 42069;





#endif //NETWORKING_HPP