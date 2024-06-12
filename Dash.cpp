#include "include/Dash.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

Dash::Dash(float arg_maximum_dash_range, sf::Sprite& arg_player, sf::RectangleShape &arg_hit_box)
    : Skills(2.0f, arg_player, arg_hit_box), maximum_dash_range(arg_maximum_dash_range) {
}

void Dash::use_skill(sf::Vector2f arg_mouse_position) {
    if (is_cooldown_off()) {
        animation_time = 0.34;
        mouse_position = arg_mouse_position;
        xy_after_dash = calc_xy(mouse_position);
        activate_cooldown();
        animation_sprite.setTexture(*player->getTexture());
        animation_sprite.setOrigin(102, 90);
        frame_number = 0;
        if (norm < maximum_dash_range)
            frame_distance = norm/20;
        else
            frame_distance = maximum_dash_range/20;

        animation_sprite.setPosition(player->getPosition());
        if (direction_vector.x > 0) {
            animation_angle = atan(direction_vector.y / direction_vector.x) * 180/M_PI;

        } else {
            animation_angle = (M_PI + atan(direction_vector.y / direction_vector.x)) * 180/M_PI;
        }
        animation_sprite.setRotation(animation_angle);
    }
}

sf::Vector2f Dash::calc_xy(const sf::Vector2f& mouse_position) {
    sf::Vector2f target_position;
    sf::Vector2f character_position = player->getPosition();
    direction_vector = mouse_position - character_position;
    norm = std::sqrt(std::pow(direction_vector.x, 2) + std::pow(direction_vector.y, 2));
    sf::FloatRect window_bounds(0.f, 0.f, 1920.f, 1080.f);
    direction_vector = direction_vector / norm;

    if (norm > maximum_dash_range) {
        target_position = character_position + direction_vector * maximum_dash_range;
    } else {
        target_position = mouse_position;
    }

    if (target_position.x< 0.f) {
        target_position.x = 0;
    } else if (target_position.x + 195 > window_bounds.width) {
        target_position.x = window_bounds.width - 195;
    }

    if (target_position.y < 0.f) {
        target_position.y = 0;
    } else if (target_position.y + 189 > window_bounds.height) {
        target_position.y = window_bounds.height - 189;
    }

    return sf::Vector2f(target_position.x,target_position.y);
}

void Dash::move_character() {
    player->setPosition(xy_after_dash);
    hit_box->setPosition(xy_after_dash);
}

void Dash::draw(sf::RenderWindow &window, float dt) {
    frame_number++;
    if (frame_number == 9) {
        move_character();
    }
    animation_time -= dt;
    if (animation_time <= 0) {
        frame_number = 0;
        return;
    }
    alpha =  12.75f * frame_number;
    animation_sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    animation_sprite.move(direction_vector * frame_distance);
    window.draw(animation_sprite);
}
