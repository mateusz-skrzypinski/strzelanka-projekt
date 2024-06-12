#ifndef SKILLS_H
#define SKILLS_H

#include <SFML/Graphics.hpp>

class Skills {
public:
    float cooldown;
    float initial_cooldown;
    sf::Sprite* player;
    sf::Vector2f mouse_position;
    float animation_time;

    Skills(float arg_cooldown, sf::Sprite &arg_player);
    virtual ~Skills() = default;

    virtual void use_skill(sf::Vector2f arg_mouse_position) = 0;
    virtual void draw(sf::RenderWindow &window, float dt) = 0;
    void activate_cooldown();
    bool is_cooldown_off();
    void change_cooldown(float new_cooldown);
};

#endif // SKILLS_H
