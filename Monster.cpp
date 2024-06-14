#include "include/Monster.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "include/trud_menu.h"


sf::Texture Monster::monster_texture;

Monster::Monster() {
    dying_time = 2; // domyslne wartosci
    damage = 1;
    attack_speed = 0.1;
    last_attack = 0;
    frame_number = 0;
    scale_factor = 3.0f;
    if (!monster_texture.loadFromFile("../../img/acolyte_monster.png")) { // ladowanie tekstury
        std::cout << "nie udalo sie" << std::endl;
    }
    this->setTexture(monster_texture);
    this->setOrigin(16, 16);

    // gora / dol - chodzenie
    frame_dimentions.emplace_back(sf::IntRect(0, 0, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(32, 0, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(64, 64, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(96, 64, 32, 32));

    // prawo / lewo - chodzenie
    frame_dimentions.emplace_back(sf::IntRect(0, 64, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(32, 64, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(0, 96, 32, 32));
    frame_dimentions.emplace_back(sf::IntRect(32, 96, 32, 32));
    setPosition(sf::Vector2f(640 + std::rand() % 1280, std::rand() % 1080)); // randowmowe rozmieszenie potworow
    hp = 20*DifficultyMenu::mnoznik_trud;   // hp i predkosc sie zmienia wraz z poziomem trudnosci
    initial_speed = 100*DifficultyMenu::mnoznik_trud; // wartosc domyslna dla predkosci - pozniej zmienna od spowolnienia
    stun = 0; // czas zamrozenia
    hit_box.setSize(sf::Vector2f(50,50)); // dodanie sztucznego hitboxa
    hit_box.setOrigin(25,25);
    hit_box.setPosition(this->getPosition());
}

void Monster::reduce_stun(float dt) { // w kazdej klatce redukcja czasu zamrozenia
    stun -= dt;
    if (stun <= 0) {
        stun = 0;
    }
}

void Monster::draw(sf::RenderWindow &window, float dt, sf::Vector2f character_xy) { // animacja
    slow_timer -= dt; // uaktualnienie czasu spowolnienia i czasu od ostatniego ataku
    last_attack += dt;
    if (stun <= 0 && hp > 0) { // jezeli nie jest zamrozony i ma wiecej niz 0 hp
        // obliczanie kierunku w ktorym idzie
        sf::Vector2f monster_xy = this->getPosition();
        sf::Vector2f dir_vector = character_xy - monster_xy;
        float norm = std::sqrt(dir_vector.x * dir_vector.x + dir_vector.y * dir_vector.y);

        if (norm != 0) {
            dir_vector = dir_vector / norm;
        }

        if (slow_timer > 0)
            speed = initial_speed * slow_factor; // nadanie spowolnienia
        else
            speed = initial_speed; // przywrocenie domyslnej wartosci predkosci

        this->move(dir_vector * speed * dt); // poruszenie sie monstera i jego hitboxa
        hit_box.move(dir_vector * speed * dt);

        // obliczanie jak powinien byc zwrocony monster lewo/prawo/gora/dol
        float alpha = std::atan2(std::abs(dir_vector.y), std::abs(dir_vector.x)) * 180 / 3.14159265;
        last_frame += dt;
        if (last_frame > 0.5f) {
            last_frame = 0;
            frame_number++;
        }

        if (frame_number >= 4) {
            frame_number = 0;
        }

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
        window.draw(*this); // rysowanie
    } else if (hp <= 0){ // jezeli ma mniej niz 1 hp, to wywoluje funkcje z animacja do umierania
        dying_animate(window, dt);
    }
    window.draw(*this); // rysowanie
}

void Monster::dying_animate(sf::RenderWindow &window, float dt) {
    if (dying_time == 2) { // dla wartosci poczatkowej zmienia jego teksture na teksture umierania
        this->setTextureRect(sf::IntRect(64,128,32,32));
    }
    dying_time -= dt; // zmniejszanie czasu jego umierania
    float alpha = 255 * (2 / dying_time); // zanikanie
    this->setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    window.draw(*this); // rysowanie
}

bool Monster::check_collision(sf::FloatRect object_rect) { // sprawdzenie czy wykonuje atak
    if (last_attack > attack_speed) {
        last_attack = 0;
        return this->getGlobalBounds().intersects(object_rect);
    }
    return false;
}
