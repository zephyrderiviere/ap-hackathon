#include "Characters.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>
#include "Combat.hpp"
#include <SFML/System/Vector2.hpp>

void Character::move(std::vector<std::vector<int>>& carte, int dx, int dy) {
    // If outside of carte, return
    if(i+dy < 0 || i+dy >= HAUTEUR_NIVEAU || j+dx < 0 || j+dx >= LARGEUR_NIVEAU) {
        return;
    }
    // Check if no collision
    switch(carte[i+dy][j+dx]) {
        case WALL:
            return;
        case POTION:
            hp += 1;
            carte[i+dy][j+dx] = NONE;
            break;
        case COIN:
            coins += 1;
            carte[i+dy][j+dx] = NONE;
            break;
        case GRAAL:
            // Implement graal logic here
            break;
        default:
            break;
    }
    // Change direction according to dx and dy
    if(dx == 1) {
        direction = RIGHT;
    } else if(dx == -1) {
        direction = LEFT;
    } else if(dy == 1) {
        direction = DOWN;
    } else if(dy == -1) {
        direction = UP;
    }

    i += dy;
    j += dx;
}

void Character::attack(std::vector<std::vector<int>>& carte) {
    // Implement attack logic here
    // Initialize the bullet at current location with direction
    Bullet bullet({(int)j, (int)i}, direction, 1, 1);
    bullets.push_back(bullet);
}

void Character::defend() {
    // Implement defend logic here
}

void Character::useItem() {
    // Implement item usage logic here
}

void Character::draw(sf::RenderWindow& window){
    sf::RectangleShape rect(sf::Vector2f(TAILLE_CASE, TAILLE_CASE));
    rect.setPosition(j*TAILLE_CASE, i*TAILLE_CASE);
    rect.setFillColor(sf::Color::Green);
    window.draw(rect);
}

sf::Vector2i Character::getPosition() {
	return sf::Vector2i(i,j);
}
