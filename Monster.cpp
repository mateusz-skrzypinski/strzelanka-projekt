#include "include/Monster.h"
#include <cstdlib>

Monster::Monster() {
    setSize(sf::Vector2f(50, 50));
    setFillColor(sf::Color::Red);
    setPosition(sf::Vector2f(640 + std::rand() % 1280, std::rand() % 1080));
    hp = 100;
    speed = 200;
    stun = 0;
}

void Monster::reduce_stun(float dt) {
    stun -= dt;
    if (stun <= 0) {
        stun = 0;
    }
}

void Monster::draw(sf::RenderWindow &window, float dt) {
    if (stun <= 0) {
        move(-speed * dt, 0);
    }
    window.draw(*this);
}
