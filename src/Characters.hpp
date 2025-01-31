#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Combat.hpp"
#include "utils.hpp"


class Character {
public:
    // default constructor
    Character() : name(""), hp(0), damage(0), defense(0), i(0), j(0), coins(0), playerID(-1), direction(UP) {};
    Character(std::string name, int hp, int attack, int defense, int i, int j, int coins, sf::Uint8 playerID = -1, int direction = UP) 
        : name(name), hp(hp), damage(attack), defense(defense), i(i), j(j), coins(coins), playerID(playerID), direction(direction) {};

    void move(std::vector<std::vector<int>>& map, int dx, int dy);
    void attack(std::vector<std::vector<int>>& carte);
    void defend();
    void useItem();
    void draw(sf::RenderWindow& window);
    std::string name;
    sf::Vector2i getPosition();

    sf::Int32 playerID;
    std::list<Bullet> bullets; // Bullet vector
    sf::Int32 i;
    sf::Int32 j;
    int coins;
    int direction;

private:
    int hp;
    int damage;
    int defense;
};

#endif // CHARACTERS_HPP
