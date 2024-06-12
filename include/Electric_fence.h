#ifndef ELECTRIC_FENCE_H
#define ELECTRIC_FENCE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Electric_fence {
public:
    static sf::Texture fence_texture;
    sf::Sprite fence_sprite;
    std::vector<sf::IntRect> frames;
    sf::RectangleShape hit_box;
    int frame_number;
    float frame_timer;
    float slow_factor;

    Electric_fence(sf::FloatRect global_bounds);
    void draw(sf::RenderWindow &window, float dt);
    bool check_collision(sf::FloatRect object_bounds);
};

#endif // ELECTRIC_FENCE_H
