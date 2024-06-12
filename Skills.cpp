#include "include/Skills.h"
#include <SFML/Graphics.hpp>

Skills::Skills(float arg_cooldown, sf::Sprite& arg_player, sf::RectangleShape &arg_hit_box)
    : cooldown(0), initial_cooldown(arg_cooldown), player(&arg_player), hit_box(&arg_hit_box) {
}

Skills::Skills(float arg_cooldown, sf::Sprite &arg_player)
    : cooldown(0), initial_cooldown(arg_cooldown), player(&arg_player) {}
void Skills::change_cooldown(float new_cooldown) {
    cooldown -= new_cooldown;
}

void Skills::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position;
}

bool Skills::is_cooldown_off() {
    return cooldown <= 0;
}

void Skills::activate_cooldown() {
    cooldown = initial_cooldown;
}

void Skills::draw(sf::RenderWindow &window, float dt) {}
