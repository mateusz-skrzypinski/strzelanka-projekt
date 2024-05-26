#include "include/Dash.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

Dash::Dash(float arg_maximum_dash_range, sf::CircleShape& arg_player)
    : Skills(2, arg_player), maximum_dash_range(arg_maximum_dash_range) {
}

void Dash::use_skill(sf::Vector2f arg_mouse_position) {
    mouse_position = arg_mouse_position;
    if (is_cooldown_off()) {
        xy_after_dash = calc_xy(mouse_position);
        move_character();
        activate_cooldown();
    }
}

sf::Vector2f Dash::calc_xy(const sf::Vector2f& mouse_position) {
    sf::Vector2f target_position;
    sf::Vector2f character_position = player->getPosition();
    sf::Vector2f direction_vector = mouse_position - character_position;
    float norm = std::sqrt(std::pow(direction_vector.x, 2) + std::pow(direction_vector.y, 2));
    sf::FloatRect window_bounds(0.f, 0.f, 1920.f, 1080.f);
    float radius = player->getRadius();

    if (norm > maximum_dash_range) {
        sf::Vector2f normalized_direction = direction_vector / norm;
        target_position = character_position + normalized_direction * maximum_dash_range;
    } else {
        target_position = mouse_position;
    }

    if (target_position.x - radius < 0.f) {
        target_position.x = radius;
    } else if (target_position.x + radius > window_bounds.width) {
        target_position.x = window_bounds.width - radius;
    }

    if (target_position.y - radius < 0.f) {
        target_position.y = radius;
    } else if (target_position.y + radius > window_bounds.height) {
        target_position.y = window_bounds.height - radius;
    }

    return sf::Vector2f(target_position.x-15,target_position.y-15);
}

void Dash::move_character() {
    player->setPosition(xy_after_dash);
}

void Dash::draw(sf::RenderWindow &window) {}
