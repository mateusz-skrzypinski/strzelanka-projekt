#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Skills.h"

class Character {
public:
    sf::CircleShape player_shape;
    Skills* skill_first_slot;
    Skills* skill_second_slot;
    float hp;

    Character();
    ~Character();

    void move(sf::Vector2f xy_distance);
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window);
};

#endif // CHARACTER_H
