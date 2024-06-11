#include "include/Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f arg_bullet_direction, Character player) {
    bullet_damage = 1;
    if (!bullet_texture.loadFromFile("../../img/bullet.png")) {
        std::cerr << "Nie udało się załadować tekstury pocisku!" << std::endl;
    }
    bullet_direction = arg_bullet_direction;
    start_position = sf::Vector2f(player.getPosition().x, player.getPosition().y);
    bullet_velocity = 500.0f;
    std::cout << "Bullet created at position: " << start_position.x << ", " << start_position.y << std::endl;
}

void Bullet::shoot_bullet() {
    this->setPosition(start_position);
    this->setTexture(bullet_texture);
    std::cout << "Bullet shot from position: " << start_position.x << ", " << start_position.y << std::endl;
}

void Bullet::move_(float dt) {
    std::cout << "before bullet move" << std::endl;
    this->move(bullet_direction * bullet_velocity * dt);
    std::cout << "Bullet moved to position: " << this->getPosition().x << ", " << this->getPosition().y << std::endl;
}

bool Bullet::is_bullet_in() {
    if (this->getPosition().x < 0 || this->getPosition().x > 1920 ||
        this->getPosition().y < 0 || this->getPosition().y > 1080) {
        std::cout << "Bullet out of bounds!" << std::endl;
        return false;
    }
    return true;
}

bool Bullet::check_collision(Monster &monster) {
    sf::FloatRect bulletBounds = this->getGlobalBounds();
    sf::FloatRect monsterBounds = monster.getGlobalBounds();

    std::cout << "Bullet bounds: " << bulletBounds.left << ", " << bulletBounds.top << ", " << bulletBounds.width << ", " << bulletBounds.height << std::endl;
    std::cout << "Monster bounds: " << monsterBounds.left << ", " << monsterBounds.top << ", " << monsterBounds.width << ", " << monsterBounds.height << std::endl;

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
