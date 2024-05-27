#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

class Monster : public sf::RectangleShape {
public:
    float hp;
    float speed;
    float stun;

    Monster();
    void reduce_stun(float dt);
    void draw(sf::RenderWindow &window, float dt);
};

#endif // MONSTER_H
