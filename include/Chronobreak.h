#ifndef CHRONOBREAK_H
#define CHRONOBREAK_H

#include "Skills.h"
#include <SFML/Graphics.hpp>

class Chronobreak : public Skills {
public:
    sf::Vector2f xy_to_teleport;
    bool is_teleport_set;
    int hp_before_teleport;
    float *player_hp;

    sf::Texture teleport_texture;;
    sf::Sprite animation_sprite;
    sf::Sprite teleport_sprite;
    int frame_number;
    bool second_animation;
    float alpha;

    Chronobreak(sf::Sprite& arg_player, float *arg_player_hp);
    void use_skill(sf::Vector2f arg_mouse_position) override;
    void teleport_character();
    void set_xy();
    void draw(sf::RenderWindow& window, float dt) override;
    void retrive_hp();
};

#endif // CHRONOBREAK_H
