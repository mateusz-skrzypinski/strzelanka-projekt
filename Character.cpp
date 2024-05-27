#include "include/Character.h"
#include "include/Dash.h"
#include <SFML/Graphics.hpp>
#include "include/Zap.h"

Character::Character()
    : player_shape(15.0f), hp(100) {
    player_shape.setPosition(0, 0);
    player_shape.setFillColor(sf::Color::Green);

    skill_first_slot = new Dash(1000.0f, player_shape);
    skill_second_slot = nullptr;
}

Character::~Character() {
    delete skill_first_slot;
    if (skill_second_slot) { // drugi skill nie musi istnieć
        delete skill_second_slot;
    }
}

void Character::move(sf::Vector2f xy_distance) {
    player_shape.move(xy_distance);
}

sf::Vector2f Character::getPosition() {
    return player_shape.getPosition();
}

void Character::setPosition(sf::Vector2f position) {
    player_shape.setPosition(position);
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(player_shape);
}
