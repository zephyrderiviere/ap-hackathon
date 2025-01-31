#include "Characters.hpp"
#include "utils.hpp"
#include <SFML/Graphics.hpp>

void Character::move(std::vector<std::vector<int>>& map, int dx, int dy) {
    // If outside of map, return
    if(i+dy < 0 || i+dy >= HAUTEUR_NIVEAU || j+dx < 0 || j+dx >= LARGEUR_NIVEAU) {
        return;
    }
    // // Move the character only if no collision
    switch(map[i+dy][j+dx]) {
        case WALL:
            return;
        case POTION:
            hp += 1;
            map[i+dy][j+dx] = NONE;
            break;
        case COIN:
            coins += 1;
            map[i+dy][j+dx] = NONE;
            break;
        case GRAAL:
            // Implement graal logic here
            break;
        default:
            break;
    }
    
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
    rect.setPosition(j*TAILLE_CASE, i*TAILLE_CASE);
    rect.setFillColor(sf::Color::Green);
    window.draw(rect);
}

Position Character::getPosition() {
	return {i,j};
}
