#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Monster : public sf::Sprite {
public:
    float hp;
    float speed;
    float stun;
    float damage;
    float attack_speed;
    float last_attack;
    float initial_speed;
    float slow_timer;
    float slow_factor;
    sf::RectangleShape hit_box;

    // animacja
    std::vector<sf::IntRect> frame_dimentions;
    static sf::Texture monster_texture;
    int frame_number;
    float scale_factor;
    float last_frame;
    float dying_time;

    Monster();
    void reduce_stun(float dt);
    void draw(sf::RenderWindow &window, float dt, sf::Vector2f character_xy);
    void dying_animate(sf::RenderWindow &window, float dt);
    bool check_collision(sf::FloatRect object_rect);
};

#endif // MONSTER_H
