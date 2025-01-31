#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Character {
public:
    // default constructor
    Character() : name(""), hp(0), damage(0), defense(0), i(0), j(0), coins(0) {};
    Character(std::string name, int hp, int attack, int defense, int i, int j, int coins) 
        : name(name), hp(hp), damage(attack), defense(defense), i(i), j(j), coins(coins) {};

    void move(std::vector<std::vector<int>>& map, int dx, int dy);
    void attack();
    void defend();
    void useItem();
    void draw(sf::RenderWindow& window);
    std::string name;

private:
    int hp;
    int damage;
    int defense;
    int i;
    int j;
    int coins;
};

#endif // CHARACTERS_HPP