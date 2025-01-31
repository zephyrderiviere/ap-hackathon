#include "Combat.hpp"
#include "utils.hpp"

int Bullet::update(std::vector<std::vector<int>>& carte) {
    // printf("Updating bullet\n, %d, %d : x %d / y %d\n",speed, direction, position.x, position.y);
    // Update the position of the bullet based on its speed and direction
    switch (direction) {
        case UP:
            position.y -= speed;
            break;
        case DOWN:
            position.y += speed;
            break;
        case LEFT:
            position.x -= speed;
            break;
        case RIGHT:
            position.x += speed;
            break;
        default:
            break;
    }
    // If any obstacle is encountered remove the bullet
    switch(carte[position.y][position.x]) {
        case WALL:
            // Delete from list
            return -1;
            break;
        default:
            break;
    }

    return 0;
}

void Bullet::draw(sf::RenderWindow& window) {
    // Draw a point representing the bullet
    sf::CircleShape blt(1);
    blt.setFillColor(sf::Color::White);
    // Draw the bullet at the center of the cell

    blt.setPosition((position.x+0.5f)*TAILLE_CASE, (position.y+0.5f)*TAILLE_CASE);
    window.draw(blt);
}

sf::Vector2i Bullet::getPosition() const {
    return sf::Vector2i(static_cast<int>(position.x), static_cast<int>(position.y));
}