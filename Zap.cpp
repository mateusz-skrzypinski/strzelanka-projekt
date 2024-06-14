#include "include/Zap.h"
#include <vector>
#include "include/Monster.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Zap::Zap(sf::Sprite &arg_player, std::vector<Monster> *arg_monsters)
    : Skills(2.0f, arg_player, "ZAP"), monsters(arg_monsters) {
    radius = 200.0f; // ustawienie domyslnych wartosci
    stun_time = 2.0f;
    damage = 5.0f;
    if (texture.loadFromFile("../../img/Zap.png")) // ladowanie tekstury
        std::cout << "Nie udalo sie zaladowac tekstury" << std::endl;
    sprite_zap.setTexture(texture);
    scale = radius / 128.0f;
    sprite_zap.setScale(scale, scale);
    using_now = false;
    // ustawienie pojedynczych klatek animacji
    frame_dimentions.emplace_back(sf::IntRect(0, 0, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(256, 0, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(512, 0, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(768, 0, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(0, 256, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(256, 256, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(512, 256, 256, 256));
    frame_dimentions.emplace_back(sf::IntRect(768, 256, 256, 256));
    animated_time = 0.0f;
    animated = 0.0f;
    frame_number = 0;
    casted = false;
}

void Zap::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position;
    if (is_cooldown_off()) { // sprawdzenie, czy mozna uzyc spella
        using_now = true; // do animacji
        sprite_zap.setPosition(mouse_position.x - radius, mouse_position.y - radius); // ustawinie pozycji
        animated_time = 0.5f;
        frame_number = 0;
        activate_cooldown();
    }
}

void Zap::draw(sf::RenderWindow& window, float dt) {
    if (!using_now) // jezeli spel nie zotsal uzyty, wychodzi z metody
        return;
    // auaktualnienie czasu animacji i czasu klatki
    animated += dt;
    animated_time -= dt;
    if (animated_time <= 0) { // jezeli czas animacji dobiegl konca, wychodzi z meteody
        using_now = false;
        react_with_monsters(); // spell sie skonczyl, wiec uruchamiana jest metoda do zadawania im obrazen i nakladania efektu stuna
        return;
    }
    if (animated > 0.0625) { // zmienianie numeru klatki
        frame_number++;
        animated = 0;
    }

    sprite_zap.setTextureRect(frame_dimentions[frame_number%frame_dimentions.size()]); // przypisywanie klatki
    window.draw(sprite_zap); // rysowanie
}

void Zap::react_with_monsters() { // zadanie obrazen i efetk zamrozenia
    sf::CircleShape zap_effect(radius); // sztuczny hitbox
    zap_effect.setPosition(mouse_position - sf::Vector2f(radius, radius)); // oblicanie jego pozycji
    for (auto& monster : *monsters) {
        if (zap_effect.getGlobalBounds().intersects(monster.getGlobalBounds())) { // jesli hitboxy na siebie nachodza:
            monster.hp -= damage; // zadaj obrazenia
            monster.stun = stun_time; // zamroz
        }
    }
}
