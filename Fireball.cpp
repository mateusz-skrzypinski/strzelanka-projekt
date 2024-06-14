#include "include/Fireball.h"
#include <vector>
#include "include/Monster.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Fireball::Fireball(sf::Sprite &arg_player, std::vector<Monster> *arg_monsters)
    : Skills(2, arg_player, "FIREBALL"), monsters(arg_monsters) {
    radius = 400.0f; // wartosci fireballa
    damage = 100.0f;
    // animacja
    using_now = false;
    animated = -0.3;
    scale = 1.5;
    texture.loadFromFile("../../img/Fireball.png");
    sprite_fireball.setTexture(texture);
    sprite_fireball.setTextureRect(sf::IntRect(0,0,32,32));
    sprite_fireball.scale(sf::Vector2f(scale,scale));
    sprite_fireball.setRotation(45);
}

void Fireball::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position; // pobranie wartosci myszki - tam leci spell
    xy_to_cast = mouse_position;
    if (is_cooldown_off()) { // sprawdzenie czy mozna uzyc spella
        using_now = true;
        sprite_fireball.setPosition(sf::Vector2f(mouse_position.x-mouse_position.y + -30,-110)); // pozycja poczatkowa
        animated_time = 1.5f; // czas animacji
        animated_speed = std::sqrt(2 * pow(mouse_position.y, 2)) * (2.0 / 3.0); // jego predkosc jest zalezna od dystansu ktory ma przeleciec
        activate_cooldown(); // aktywacja czasu odnowienia
    }
}

void Fireball::react_with_monsters() {
    sf::CircleShape fireball(radius); // sztuczny hitbox, do sprawdzenia trafienia
    fireball.setPosition(xy_to_cast - sf::Vector2f(radius, radius));
    for (auto& monster : *monsters) {
        if (fireball.getGlobalBounds().intersects(monster.getGlobalBounds())) {
            monster.hp -= damage; // zadawanie obrazen
        }
    }
}

void Fireball::draw(sf::RenderWindow& window, float dt) { // animacja
    if (!using_now) // jesli nie zostal uzyty, to nic nie rysuje
        return;

    if (animated_time != 0) {
        scale = 1.5 * std::exp((1.5 - animated_time / 1.5) * std::log(2)); // fireball rosnie wykladniczo (tylko animacja)
        sprite_fireball.setScale(sf::Vector2f(scale,scale)); // ustawienie skalowania w kazdej klatce
        if (animated > 0) { // animcja z dwoma klatkami - zmienianie tych klatek
            sprite_fireball.setTextureRect(sf::IntRect(32,0,32,32));
        } else {
            sprite_fireball.setTextureRect(sf::IntRect(0,0,32,32));
        }
        animated += dt; // zmienianie klatek
        if (animated > 0.3) {
            animated = -0.3;
        }
        sprite_fireball.move(sf::Vector2f(animated_speed/sqrt(2)*dt,animated_speed/sqrt(2) *dt)); // poruszanie fireball
        window.draw(sprite_fireball); // rysowanie
    }
    animated_time -= dt;
    if (animated_time <= 0) { // jesli calkowity czas animacji jest mniejszy od zera, to fireball juz trafil w ziemie
        using_now = false; // reset
        animated_time = 0; // reset
        react_with_monsters(); // wiec zadaje damage potworkom
    }
} // animacja
