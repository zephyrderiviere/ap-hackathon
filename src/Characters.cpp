#include "Characters.hpp"
#include <SFML/Graphics.hpp>


Character::Character(std::string name, int hp, int damage, int defense, int x, int y)
    : name(name), hp(hp), damage(damage), defense(defense), x(x), y(y) {}

void Character::move(int dx, int dy) {
    x += dx;
    y += dy;
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
    int size = 40;
    sf::RectangleShape rect(sf::Vector2f(size, size));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Red);
    window.draw(rect);
}