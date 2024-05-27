#ifndef ZAP_H
#define ZAP_H

#include "Skills.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Monster.h"

class Zap : public Skills {
public:
    sf::Vector2f xy_to_cast;
    float radius;
    float stun_time;
    float damage;
    std::vector<Monster> *monsters;

    Zap(sf::CircleShape& arg_player, std::vector<Monster> *arg_monsters);
    void use_skill(sf::Vector2f arg_mouse_position) override;
    void draw(sf::RenderWindow& window) override;
    void react_with_monsters();
};

#endif // ZAP_H
