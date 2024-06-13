#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"
#include "Monster.h"
#include "Character.h" // Dodaj plik nagłówkowy dla klasy Character

class Bullet : public sf::Sprite {
public:
    float bullet_velocity;
    sf::Vector2f bullet_direction;
    sf::Vector2f start_position;

    static sf::Texture bullet_texture;

    Bullet(sf::Vector2f arg_bullet_direction, sf::Vector2f character_xy);
    void shoot_bullet();
    void move_(float dt);
    bool is_bullet_in();
    bool check_collision(Monster &monster);
    void drawBounds(sf::RenderTarget& target, sf::RenderStates states) const; // Dodajemy metodę do rysowania granic pocisku
};

#endif // BULLET_H
