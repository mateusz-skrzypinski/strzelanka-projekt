#include "include/Chronobreak.h"
#include <iostream>

Chronobreak::Chronobreak(sf::Sprite &arg_player, sf::RectangleShape &arg_hit_box, int *arg_player_hp)
    : Skills(2.0f, arg_player, arg_hit_box, "TELEPORT"), player_hp(arg_player_hp) {
    teleport_texture.loadFromFile("../../img/Teleport.png");
    teleport_sprite.setTexture(teleport_texture);
    teleport_sprite.setOrigin(teleport_sprite.getGlobalBounds().width/2, teleport_sprite.getGlobalBounds().height/2);
    is_teleport_set = false;
    second_animation = true;
    animation_time = 0;
}

void Chronobreak::use_skill(sf::Vector2f arg_mouse_position) {
    if (is_cooldown_off()) {
        frame_number = 0;
        mouse_position = arg_mouse_position;
        if (is_teleport_set) {
            frame_number = 0;
            animation_time = 1.5f;
            is_teleport_set = false;
            activate_cooldown();
        } else {
            teleport_sprite.setPosition(player->getPosition());
            set_xy();
            second_animation = true;
            is_teleport_set = true;
            hp_before_teleport = *player_hp;
            animation_sprite.setTexture(*player->getTexture());
            activate_cooldown();
        }
    }
}

void Chronobreak::set_xy() {
    xy_to_teleport = player->getPosition();
}

void Chronobreak::teleport_character() {
    player->setPosition(xy_to_teleport);
    hit_box->setPosition(xy_to_teleport);
    retrive_hp();
}

void Chronobreak::draw(sf::RenderWindow& window, float dt) { // animacja
    animation_time -= dt;

    if (is_teleport_set || animation_time > 0)
        window.draw(teleport_sprite);
    if (animation_time <= 0) {
        frame_number = 0;
        return;
    }
    if (animation_time > 0) {

        frame_number++;
        if (animation_time > 0.75f) {
            // pierwsza czesc, gdzie znika w miejcu
            if (frame_number == 0)
                alpha = 1;
            else
                alpha = frame_number * -0.0215f + 1.0215;
            player->setScale(alpha, alpha);
        }
        else {
            // druga czesc, gdzie pojawia sie na miejscu teleporta
            if (second_animation) {
                second_animation = false;
                teleport_character();
            }
            else {
                if (frame_number == 0)
                    alpha = 0.051;
                else if (frame_number >= 89) {
                    player->setScale(1,1);
                }
                else {
                    alpha = frame_number * 0.022f - 0.981;
                    player->setScale(alpha, alpha);
                }
            }
        }
    }
}

void Chronobreak::retrive_hp() {
    *player_hp = hp_before_teleport;
}
