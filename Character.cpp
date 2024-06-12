#include "include/Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/trud_menu.h"
#include <cmath>

Character::Character() {
    is_walking = false;
    is_shooting = false;
    skill_first_slot = nullptr;
    skill_second_slot = nullptr;
    load_texture();
    player_sprite.setOrigin(102,90);
    hit_box.setSize(sf::Vector2f(80, 75));
    hit_box.setOrigin(40, 40);
    hit_box.setPosition(385,315);
    hit_box.setFillColor(sf::Color::Red);
    hp = 100;
    top = 0;
    right = 0;
    initial_speed = 400.0f/DifficultyMenu::mnoznik_trud; //gracz jest wolniejszy jesli ma wyzszy poziom trudnosci
}


Character::~Character() {
    delete skill_first_slot;
    if (skill_second_slot) { // drugi skill nie musi istnieć
        delete skill_second_slot;
    }
}

void Character::move(sf::Vector2f xy_distance) {
    if (slow_timer > 0)
        xy_distance *= slow_factor;
    player_sprite.move(xy_distance);
    hit_box.move(xy_distance);
    if (top == 0 && right == 1)
        player_sprite.setRotation(0);
    if (top == -1 && right == 1)
        player_sprite.setRotation(-45.0f);
    if (top == -1 && right == 0)
        player_sprite.setRotation(-90.0f);
    if (top == -1 && right == -1)
        player_sprite.setRotation(-135.0f);
    if (top == 0 && right == -1)
        player_sprite.setRotation(-180.0f);
    if (top == 1 && right == -1)
        player_sprite.setRotation(-225.0f);
    if (top == 1 && right == 0)
        player_sprite.setRotation(-270.0f);
    if (top == 1 && right == 1)
        player_sprite.setRotation(-315.0f);
    top = 0;
    right = 0;
}

sf::Vector2f Character::getPosition() {
    return player_sprite.getPosition();
}

void Character::setPosition(sf::Vector2f position) {
    player_sprite.setPosition(position);
}

void Character::draw(sf::RenderWindow& window, float dt, sf::Vector2f mouse_xy) {
    slow_timer -= dt;
    if (!is_walking && !is_shooting) {
        speed = initial_speed;
        player_sprite.setTexture(peace_texture);
        window.draw(player_sprite);
        return;
    }

    last_frame_time += dt;
    if (last_frame_time > 0.05f) {
        last_frame_time = 0;
        frame_number++;
    }
    if (frame_number > 20) {
        frame_number = 0;
    }

    if (is_shooting) {
        speed = initial_speed/2;
        if (frame_number < static_cast<int>(shooting_texture.size())) {
            player_sprite.setTexture(shooting_texture[frame_number]);
        } else {
            std::cout << "Error: frame_number (" << frame_number << ") out of range for shooting_texture" << std::endl;
        }

        float alpha;
        sf::Vector2f dir_vector = mouse_xy - getPosition();
        float norm = std::sqrt(dir_vector.x * dir_vector.x + dir_vector.y * dir_vector.y);
        if (norm != 0) {
            dir_vector = dir_vector / norm;
        }

        if (dir_vector.x > 0) {
            alpha = atan(dir_vector.y / dir_vector.x) * 180/M_PI;

        } else {
            alpha = (M_PI + atan(dir_vector.y / dir_vector.x)) * 180/M_PI;
        }
        player_sprite.setRotation(alpha);
    } else {
        speed = initial_speed;
        if (frame_number < static_cast<int>(walking_texture.size())) {
            player_sprite.setTexture(walking_texture[frame_number]);
        } else {
            std::cout << "Error: frame_number (" << frame_number << ") out of range for walking_texture" << std::endl;
        }
    }
    window.draw(player_sprite);
    is_walking = false;
    is_shooting = false;
}


void Character::load_texture() {
    peace_texture.loadFromFile("../../img/walk/6.png");
    for (int i = 1; i <= 21; i++) {
        std::string shooting_file_name = "../../img/attack/";
        std::string walking_file_name = "../../img/walk/";
        sf::Texture walking;
        if (!walking.loadFromFile(walking_file_name + std::to_string(i) + ".png"))
            std::cout << "nie udalo sie zaladowac tekstur" << std::endl;
        walking_texture.emplace_back(walking);
        sf::Texture shooting;
        if (!shooting.loadFromFile(shooting_file_name + std::to_string(i) + ".png"))
            std::cout << "nie udalo sie zaladowac tekstury" << std::endl;
        shooting_texture.emplace_back(shooting);
    }
}
