#include "include/Zap.h"
#include <vector>
#include "include/Monster.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Zap::Zap(sf::CircleShape &arg_player, std::vector<Monster> *arg_monsters)
    : Skills(2, arg_player), monsters(arg_monsters) {
    radius = 400.0f;
    stun_time = 2.0f;
    damage = 20.0f;
}

void Zap::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position;
    xy_to_cast = mouse_position;
    if (is_cooldown_off()) {
        react_with_monsters();
        activate_cooldown();
    }
}

void Zap::react_with_monsters() {
    sf::CircleShape zap(radius);
    zap.setPosition(xy_to_cast - sf::Vector2f(radius, radius));
    for (auto& monster : *monsters) {
        if (zap.getGlobalBounds().intersects(monster.getGlobalBounds())) {
            monster.hp -= damage;
            monster.stun += stun_time;
        }
    }
}

void Zap::draw(sf::RenderWindow& window) {} // animacja
