#ifndef COMBAT_HPP
#define COMBAT_HPP

#include <SFML/Graphics.hpp>

class Bullet {

    public:
        Bullet(sf::Vector2i position, int direction, int speed, int damage) 
            : position(position), direction(direction), speed(speed), damage(damage) {};

        int update(std::vector<std::vector<int>>& carte);
        void draw(sf::RenderWindow& window);
        sf::Vector2i getPosition() const;
        // Overload == operator
        bool operator==(const Bullet& b) const {
            return position == b.position && direction == b.direction && speed == b.speed;
        }

    private:
        sf::Vector2i position;
        int direction;
        int speed; 
        int damage;
};

#endif // COMBAT_HPP