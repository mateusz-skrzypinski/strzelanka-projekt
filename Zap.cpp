#include "include/Zap.h"
#include <vector>
#include "include/Monster.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Zap::Zap(sf::Sprite &arg_player, std::vector<Monster> *arg_monsters)
    : Skills(2.0f, arg_player), monsters(arg_monsters) {
    radius = 200.0f;
    stun_time = 2.0f;
    damage = 20.0f;
    texture.loadFromFile("../../img/Zap.png");
    sprite_zap.setTexture(texture);
    scale = radius / 128.0f;
    sprite_zap.setScale(scale, scale);
    using_now = false;
    frame_dimentions.emplace_back(sf::IntRect(0, 0, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(256, 0, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(512, 0, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(768, 0, 256, 256));
    animated_time = 0.0f;
    animated = 0.0f;
    frame_number = 0;
    casted = false;
}

void Zap::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position;
    if (is_cooldown_off()) {
        using_now = true;
        sprite_zap.setPosition(mouse_position.x - radius, mouse_position.y - radius);
        animated_time = 0.5f;
        frame_number = 0;
        activate_cooldown();
    }
}

void Zap::draw(sf::RenderWindow& window, float dt) {
    if (!using_now) return;

    animated_time -= dt;
    if (animated_time <= 0) {
        using_now = false;
        react_with_monsters();
        return;
    }

    frame_number = (frame_number + 1) % frame_dimentions.size();
    sprite_zap.setTextureRect(frame_dimentions[frame_number]);
    window.draw(sprite_zap);
}

void Zap::react_with_monsters() {
    sf::CircleShape zap_effect(radius);
    zap_effect.setPosition(mouse_position - sf::Vector2f(radius, radius));
    for (auto& monster : *monsters) {
        if (zap_effect.getGlobalBounds().intersects(monster.getGlobalBounds())) {
            monster.hp -= damage;
            monster.stun = stun_time;
        }
    }
}
