#include "include/Character.h"
#include "include/Dash.h"
#include "include/Chronobreak.h"
#include <SFML/Graphics.hpp>

Character::Character()
    : player_shape(15.0f), hp(100) {
    player_shape.setPosition(0, 0);
    player_shape.setFillColor(sf::Color::Green);

    skill_first_slot = new Dash(1000.0f, player_shape);
    skill_second_slot = new Chronobreak(player_shape, &hp);
}

Character::~Character() {
    delete skill_first_slot;
    delete skill_second_slot;
}

void Character::move(sf::Vector2f xy_distance) {
    player_shape.move(xy_distance);
}

sf::Vector2f Character::getPosition() {
    return player_shape.getPosition();
}
