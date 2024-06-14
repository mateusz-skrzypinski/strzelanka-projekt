#include "include/Bullet.h"
#include <iostream>
#include <cmath>

sf::Texture Bullet::bullet_texture;

Bullet::Bullet(sf::Vector2f arg_bullet_direction, sf::Vector2f character_xy) {
    if (!bullet_texture.loadFromFile("../../img/bullet.png")) {
        std::cout << "Nie udało się załadować tekstury pocisku!" << std::endl;
    }
    bullet_direction = arg_bullet_direction; // kierunek w którym leci pocisk
    start_position = character_xy;
    this->setOrigin(this->getGlobalBounds().width/2, this->getGlobalBounds().height/2);
    float alpha; // kąt obrotu pocisku
    if (bullet_direction.x > 0) {
        alpha = atan(bullet_direction.y / bullet_direction.x) * 180/M_PI;

    } else {
        alpha = (M_PI + atan(bullet_direction.y / bullet_direction.x)) * 180/M_PI;
    }
    this->setRotation(alpha);
    bullet_velocity = 1500.0f;
    hit_box.setSize(sf::Vector2f(6,4)); // dodanie hitboxa
    hit_box.setOrigin(3,2);
    hit_box.setRotation(alpha);
}

void Bullet::shoot_bullet() { // inicjalizacja po strzale - zaladiwanie tekstury i pozycja
    this->setPosition(start_position);
    hit_box.setPosition(start_position);
    this->setTexture(bullet_texture);
}

void Bullet::move_(float dt) { // poruszanie pociskiem
    this->move(bullet_direction * bullet_velocity * dt);
    hit_box.move(bullet_direction * bullet_velocity * dt);
}

bool Bullet::is_bullet_in() { // sprawdzenie, czy pocisk dalej jest w obrebie okna
    if (hit_box.getPosition().x < 0 || hit_box.getPosition().x > 1920 ||
        hit_box.getPosition().y < 0 || hit_box.getPosition().y > 1080) {
        return false;
    }
    return true;
}

bool Bullet::check_collision(sf::FloatRect object_bounds) { // sprawdzenie, czy pocisk na cos trafil
    sf::FloatRect bulletBounds = hit_box.getGlobalBounds();
    return bulletBounds.intersects(object_bounds);
}
