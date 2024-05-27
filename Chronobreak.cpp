#include "include/Chronobreak.h"

Chronobreak::Chronobreak(sf::CircleShape &arg_player, float *arg_player_hp)
    : Skills(2, arg_player), player_hp(arg_player_hp) {
    teleport.setRadius(15.0f);
    teleport.setFillColor(sf::Color::Blue);
    is_teleport_set = false;
}

void Chronobreak::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position;
    if (is_cooldown_off()) {
        if (is_teleport_set) {
            teleport_character();
            is_teleport_set = false;
            activate_cooldown();
        } else {
            teleport.setPosition(player->getPosition());
            set_xy();
            is_teleport_set = true;
            hp_before_teleport = *player_hp;
            activate_cooldown();
        }
    }
}

void Chronobreak::set_xy() {
    xy_to_teleport = player->getPosition();
}

void Chronobreak::teleport_character() {
    player->setPosition(xy_to_teleport);
    retrive_hp();
}

void Chronobreak::draw(sf::RenderWindow& window) { // animacja
    if (is_teleport_set) {
        window.draw(teleport);
    }
}

void Chronobreak::retrive_hp() {
    *player_hp = hp_before_teleport;
}
