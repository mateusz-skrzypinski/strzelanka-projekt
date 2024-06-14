#include "include/Dash.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

Dash::Dash(float arg_maximum_dash_range, sf::Sprite& arg_player, sf::RectangleShape &arg_hit_box)
    : Skills(2.0f, arg_player, arg_hit_box, "DASH"), maximum_dash_range(arg_maximum_dash_range) {
}

void Dash::use_skill(sf::Vector2f arg_mouse_position) {
    if (is_cooldown_off()) { // sprawdzenie czy mozna uzyc umiejetnosc
        animation_time = 0.34;
        mouse_position = arg_mouse_position; // przwchytywanie pozycji myszki, zeby obliczyc wektor skoku
        xy_after_dash = calc_xy(mouse_position); // obliczanie tego wektora
        activate_cooldown(); // aktywacja czasu odnowienia
        animation_sprite.setTexture(*player->getTexture());
        animation_sprite.setOrigin(102, 90);
        frame_number = 0;
        if (norm < maximum_dash_range)
            frame_distance = norm/20;
        else
            frame_distance = maximum_dash_range/20;

        animation_sprite.setPosition(player->getPosition()); // pobranie pozycji gracza
        if (direction_vector.x > 0) { // obliczenie kata rotacji skoku
            animation_angle = atan(direction_vector.y / direction_vector.x) * 180/M_PI;

        } else {
            animation_angle = (M_PI + atan(direction_vector.y / direction_vector.x)) * 180/M_PI;
        }
        animation_sprite.setRotation(animation_angle); // nadanie kata rotacji skoku
    }
}

sf::Vector2f Dash::calc_xy(const sf::Vector2f& mouse_position) { // obliczanie wektora skoku
    sf::Vector2f target_position;
    sf::Vector2f character_position = player->getPosition();
    direction_vector = mouse_position - character_position; // wektor kierunkowy
    norm = std::sqrt(std::pow(direction_vector.x, 2) + std::pow(direction_vector.y, 2));
    sf::FloatRect window_bounds(0.f, 0.f, 1920.f, 1080.f);
    direction_vector = direction_vector / norm; // wektor kierunkowy, jednostkowy

    if (norm > maximum_dash_range) { // pozycja po skoku
        target_position = character_position + direction_vector * maximum_dash_range;
    } else {
        target_position = mouse_position;
    }

    // warunki, zeby nie dalo sie skoczyc poza mape
    if (target_position.x< 0.f) {
        target_position.x = 0;
    } else if (target_position.x > window_bounds.width) {
        target_position.x = window_bounds.width ;
    }

    if (target_position.y < 0.f) {
        target_position.y = 0;
    } else if (target_position.y > window_bounds.height) {
        target_position.y = window_bounds.height;
    }

    // zwrocenie wektora miejsca x,y do ktorego ma skoczyc
    return sf::Vector2f(target_position.x,target_position.y);
}

void Dash::move_character() { // wykonanie skoku dla gracza i hit_boxa
    player->setPosition(xy_after_dash);
    hit_box->setPosition(xy_after_dash);
}

void Dash::draw(sf::RenderWindow &window, float dt) { // animacja
    frame_number++;
    if (frame_number == 19) {
        move_character();
    }
    animation_time -= dt;
    if (animation_time <= 0) {
        frame_number = 0; // resetowanie, gdy nie jest wykonywana animacja
        return;
    }
    alpha =  12.75f * frame_number; // wspolczynnik przezroczystosci, w kazdej klatce animacji jest wyzszy
    animation_sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    animation_sprite.move(direction_vector * frame_distance); // kazda klata animacji skacze o ustalony dystans
    window.draw(animation_sprite);
}
