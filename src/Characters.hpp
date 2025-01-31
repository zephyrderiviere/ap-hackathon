#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <SFML/Graphics.hpp>


class Character {
public:
    // default constructor
    Character() : name(""), hp(0), damage(0), defense(0), i(0), j(0), coins(5), playerID(-1) {};
    Character(std::string name, int hp, int attack, int defense, int i, int j, int coins, sf::Int32 playerID = -1) 
        : name(name), hp(hp), damage(attack), defense(defense), i(i), j(j), coins(coins), playerID(playerID) {};

    void move(std::vector<std::vector<int>>& map, int dx, int dy);
    void attack();
    void defend();
    void useItem();
    void draw(sf::RenderWindow& window);
    std::string name;
    sf::Vector2i getPosition();

    sf::Int32 playerID;
    sf::Int32 i;
    sf::Int32 j;
    int coins;

private:
    int hp;
    int damage;
    int defense;
};

#endif // CHARACTERS_HPP
