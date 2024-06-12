#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"
#include "Monster.h"
#include "Character.h"

class Bullet : public sf::Sprite {
public:
    float bullet_velocity;
    sf::Vector2f bullet_direction;
    sf::Vector2f start_position;
    sf::RectangleShape hit_box;

    static sf::Texture bullet_texture;

    Bullet(sf::Vector2f arg_bullet_direction, sf::Vector2f character_xy);
    void shoot_bullet();
    void move_(float dt);
    bool is_bullet_in();
    bool check_collision(sf::FloatRect object_bounds);
    void drawBounds(sf::RenderTarget& target, sf::RenderStates states) const; // Dodajemy metodę do rysowania granic pocisku
};

#endif // BULLET_H
