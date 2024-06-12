#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Skills.h"

class Character {
public:
    Skills* skill_first_slot;
    Skills* skill_second_slot;
    int hp;
    float speed;
    std::string name_of_skill;

    sf::Sprite player_sprite;
    sf::RectangleShape hit_box;
    std::vector<sf::Texture> walking_texture;
    std::vector<sf::Texture> shooting_texture;
    sf::Texture peace_texture;
    bool is_shooting;
    int frame_number;
    float last_frame_time;
    bool is_walking;
    int top;
    int right;

    Character();
    ~Character();
    void move(sf::Vector2f xy_distance);
    void load_texture();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window, float dt, sf::Vector2f mouse_xy);
};

#endif // CHARACTER_H
