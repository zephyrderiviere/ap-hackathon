#include "Characters.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>

void Character::move(int dx, int dy) {
    i += dy;
    j += dx;
}

void Character::attack() {
    // Implement attack logic here
}

void Character::defend() {
    // Implement defend logic here
}

void Character::useItem() {
    // Implement item usage logic here
}

void Character::draw(sf::RenderWindow& window){
    sf::RectangleShape rect(sf::Vector2f(TAILLE_CASE, TAILLE_CASE));
    rect.setPosition(i*TAILLE_CASE, j*TAILLE_CASE);
    rect.setFillColor(sf::Color::Red);
    window.draw(rect);
}