#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Monster : public sf::Sprite {
public:
    float hp;
    float speed;
    float stun;

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
};

#endif // MONSTER_H
