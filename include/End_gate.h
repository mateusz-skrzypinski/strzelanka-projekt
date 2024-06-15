#ifndef END_GATE_H
#define END_GATE_H

#include <SFML/Graphics.hpp>

class End_gate : public sf::Sprite {
public:
    sf::Texture end_gate_texture;
    float timer;
    float time;

    End_gate();
    bool check_collision(sf::FloatRect object_rect);
};

#endif // END_GATE_H
