#include "include/Bullet.h"
#include <iostream>
#include <cmath>

sf::Texture Bullet::bullet_texture;

Bullet::Bullet(sf::Vector2f arg_bullet_direction, sf::Vector2f character_xy) {
    if (!bullet_texture.loadFromFile("../../img/bullet.png")) {
        std::cerr << "Nie udało się załadować tekstury pocisku!" << std::endl;
    }
    bullet_direction = arg_bullet_direction;
    start_position = character_xy;
    this->setOrigin(this->getGlobalBounds().width/2, this->getGlobalBounds().height/2);
    float alpha;
    if (bullet_direction.x > 0) {
        alpha = atan(bullet_direction.y / bullet_direction.x) * 180/M_PI;

    } else {
        alpha = (M_PI + atan(bullet_direction.y / bullet_direction.x)) * 180/M_PI;
    }
    this->setRotation(alpha);
    bullet_velocity = 1500.0f;
}

void Bullet::shoot_bullet() {
    this->setPosition(start_position);
    this->setTexture(bullet_texture);
}

void Bullet::move_(float dt) {
    this->move(bullet_direction * bullet_velocity * dt);
}

bool Bullet::is_bullet_in() {
    if (this->getPosition().x < 0 || this->getPosition().x > 1920 ||
        this->getPosition().y < 0 || this->getPosition().y > 1080) {
        return false;
    }
    return true;
}

bool Bullet::check_collision(Monster &monster) {
    sf::FloatRect bulletBounds = this->getGlobalBounds();
    sf::FloatRect monsterBounds = monster.getGlobalBounds();
    return bulletBounds.intersects(monsterBounds);
}

void Bullet::drawBounds(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::FloatRect bounds = getGlobalBounds();
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1.f);
    rect.setOutlineColor(sf::Color::Red);
    target.draw(rect, states);
}
