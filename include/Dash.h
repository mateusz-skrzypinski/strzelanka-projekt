#ifndef DASH_H
#define DASH_H

#include "Skills.h"
#include <SFML/Graphics.hpp>

class Dash : public Skills {
public:
    sf::Vector2f xy_after_dash;
    float maximum_dash_range;

    Dash(float arg_maximum_dash_range, sf::CircleShape& arg_player);
    void use_skill(sf::Vector2f arg_mouse_position) override;
    sf::Vector2f calc_xy(const sf::Vector2f& mouse_position);
    void move_character();
    void draw(sf::RenderWindow &window, float dt);
};

#endif // DASH_H