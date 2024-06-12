#include "include/Monster.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "include/trud_menu.h"

sf::Texture Monster::monster_texture;

Monster::Monster() {
    dying_time = 2;
    frame_number = 0;
    scale_factor = 3.0f;
    if (!monster_texture.loadFromFile("../../img/acolyte_monster.png")) {
        std::cout << "nie udalo sie" << std::endl;
    }
    this->setTexture(monster_texture);
    this->setOrigin(16, 16);

    // gora / dol
    frame_dimentions.emplace_back(sf::IntRect(0, 0, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(32, 0, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(64, 64, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(96, 64, 32, 32));

    // prawo / lewo
    frame_dimentions.emplace_back(sf::IntRect(0, 64, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(32, 64, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(0, 96, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(32, 96, 32, 32));
    setPosition(sf::Vector2f(640 + std::rand() % 1280, std::rand() % 1080));
    hp = 20*DifficultyMenu::mnoznik_trud;   //hp i predkosc sie zmienia wraz z poziomem trudnosci
    speed = 100*DifficultyMenu::mnoznik_trud;
    stun = 0;
}

void Monster::reduce_stun(float dt) {
    stun -= dt;
    if (stun <= 0) {
        stun = 0;
    }
}

void Monster::draw(sf::RenderWindow &window, float dt, sf::Vector2f character_xy) {
    if (stun <= 0 && hp > 0) {
        sf::Vector2f monster_xy = this->getPosition();
        sf::Vector2f dir_vector = character_xy - monster_xy;
        float norm = std::sqrt(dir_vector.x * dir_vector.x + dir_vector.y * dir_vector.y);

        if (norm != 0) {
            dir_vector = dir_vector / norm;
        }

        this->move(dir_vector * speed * dt);

        float alpha = std::atan2(std::abs(dir_vector.y), std::abs(dir_vector.x)) * 180 / 3.14159265;
        last_frame += dt;
        if (last_frame > 0.5f) {
            last_frame = 0;
            frame_number++;
        }

        if (frame_number >= 4) {
            frame_number = 0;
        }

        // Set scale before setting texture rect
        this->setScale(scale_factor, scale_factor);

        if (dir_vector.x > 0 && dir_vector.y > 0) {
            if (alpha >= 45) {
                this->setTextureRect(frame_dimentions[frame_number]);
            } else {
                this->setTextureRect(frame_dimentions[4 + frame_number]);
            }
        } else if (dir_vector.x < 0 && dir_vector.y > 0) {
            if (alpha >= 45) {
                this->setTextureRect(frame_dimentions[frame_number]);
            } else {
                this->setScale(scale_factor * -1, scale_factor * 1);
                this->setTextureRect(frame_dimentions[4 + frame_number]);
            }
        } else if (dir_vector.x < 0 && dir_vector.y < 0) {
            if (alpha >= 45) {
                this->setTextureRect(frame_dimentions[frame_number]);
            } else {
                this->setScale(scale_factor * -1, scale_factor * 1);
                this->setTextureRect(frame_dimentions[4 + frame_number]);
            }
        } else if (dir_vector.x > 0 && dir_vector.y < 0) {
            if (alpha >= 45) {
                this->setTextureRect(frame_dimentions[frame_number]);
            } else {
                this->setTextureRect(frame_dimentions[4 + frame_number]);
            }
        }
        window.draw(*this);
    } else if (hp <= 0){
        dying_animate(window, dt);
    }
    window.draw(*this);
}

void Monster::dying_animate(sf::RenderWindow &window, float dt) {
    if (dying_time == 2) {
        this->setTextureRect(sf::IntRect(64,128,32,32));
    }
    dying_time -= dt;
    float alpha = 255 * (2 / dying_time);
    this->setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    window.draw(*this);
}
