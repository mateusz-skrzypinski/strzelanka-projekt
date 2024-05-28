#include "include/Zap.h"
#include <vector>
#include "include/Monster.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Zap::Zap(sf::CircleShape &arg_player, std::vector<Monster> *arg_monsters)
    : Skills(2, arg_player), monsters(arg_monsters) {
    radius = 200.0f;
    stun_time = 2.0f;
    damage = 20.0f;
    texture.loadFromFile("C:/Users/jacek/Documents/zadanie7_2/resources/Zap.png");
    sprite_zap.setTexture(texture);
    scale = radius/128;
    std::cout << scale << std::endl;
    sprite_zap.scale(sf::Vector2f(scale,scale));
    using_now = false;
    // ustawiam klatki
    frame_dimentions.emplace_back(sf::IntRect(0,256,256,256));
    frame_dimentions.emplace_back(sf::IntRect(0,0,256,256));
    frame_dimentions.emplace_back(sf::IntRect(256,0,256,256));
    frame_dimentions.emplace_back(sf::IntRect(512,0,256,256));
    frame_dimentions.emplace_back(sf::IntRect(768,0,256,256));
    frame_dimentions.emplace_back(sf::IntRect(256,256,256,256));
    frame_dimentions.emplace_back(sf::IntRect(512,256,256,256));
    frame_dimentions.emplace_back(sf::IntRect(768,256,256,256));
}

void Zap::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position;
    xy_to_cast = mouse_position;
    if (is_cooldown_off()) {
        sprite_zap.setPosition(sf::Vector2f(mouse_position.x - radius, mouse_position.y - radius));
        std::cout << sprite_zap.getPosition().x << "  " << sprite_zap.getPosition().y << std::endl;
        activate_cooldown();
        animated_time = 0;
        using_now = true;
        casted = false;
        frame_number = 0;
    }
}

void Zap::react_with_monsters() {
    sf::CircleShape zap(radius);
    zap.setPosition(xy_to_cast - sf::Vector2f(radius, radius));
    for (auto& monster : *monsters) {
        if (zap.getGlobalBounds().intersects(monster.getGlobalBounds())) {
            monster.hp -= damage;
            std::cout << monster.hp << std::endl;
            monster.stun += stun_time;
        }
    }
}

void Zap::draw(sf::RenderWindow& window, float dt) {
    if (!using_now) return;

    animated_time += dt;
    int total_frames = frame_dimentions.size();
    float frame_duration = 0.1f;
    if (animated_time >= frame_duration) {
        animated_time -= frame_duration;
        frame_number++;
        if (frame_number >= total_frames) {
            using_now = false;
            return;
        }
    }
    sprite_zap.setTextureRect(frame_dimentions[frame_number]);
    window.draw(sprite_zap);
    if (frame_number == 4 && !casted) {
        std::cout << "react with monster\n";
        react_with_monsters();
        casted = true;
    }
} // animacja
