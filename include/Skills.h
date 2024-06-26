#ifndef SKILLS_H
#define SKILLS_H

#include <SFML/Graphics.hpp>
#include <string>

class Skills {
public:
    std::string name;

    float cooldown;
    float initial_cooldown;
    sf::Sprite* player;
    sf::RectangleShape *hit_box;
    sf::Vector2f mouse_position;
    float animation_time;

    Skills(float arg_cooldown, sf::Sprite &arg_player, sf::RectangleShape &arg_hit_box, std::string name);
    Skills(float arg_cooldown, sf::Sprite &arg_player, std::string name);
    virtual ~Skills() = default;

    virtual void use_skill(sf::Vector2f arg_mouse_position) = 0;
    virtual void draw(sf::RenderWindow &window, float dt) = 0;
    void activate_cooldown();
    bool is_cooldown_off();
    void change_cooldown(float new_cooldown);
};

#endif // SKILLS_H
