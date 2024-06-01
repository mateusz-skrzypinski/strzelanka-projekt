#ifndef FIREBALL_H
#define FIREBALL_H

#include "Skills.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Monster.h"

class Fireball : public Skills {
public:
    sf::Vector2f xy_to_cast;
    float radius;
    float damage;
    std::vector<Monster> *monsters;

    // animacja
    sf::Texture texture;
    sf::Sprite sprite_fireball;
    float animated_time;
    float animated_speed;
    bool using_now;
    float animated;
    float scale;

    Fireball(sf::CircleShape& arg_player, std::vector<Monster> *arg_monsters);
    void use_skill(sf::Vector2f arg_mouse_position) override;
    void draw(sf::RenderWindow& window, float dt) override;
    void react_with_monsters();
};

#endif // FIREBALL_H
