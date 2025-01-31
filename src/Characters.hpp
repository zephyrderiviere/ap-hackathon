#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Character {
public:
    Character(std::string name, int hp, int attack, int defense, int x, int y);

    void move(int dx, int dy);
    void attack();
    void defend();
    void useItem();
    void draw(sf::RenderWindow& window);
    std::string name;

private:
    int hp;
    int damage;
    int defense;
    int x;
    int y;
};

#endif // CHARACTERS_HPP