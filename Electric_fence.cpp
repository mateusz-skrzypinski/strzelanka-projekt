#include "include/Electric_fence.h"
#include "include/trud_menu.h"

sf::Texture Electric_fence::fence_texture;                      // global bounds to tylko nazwa

Electric_fence::Electric_fence(sf::FloatRect global_bounds) {   // Left - polozenie x
    fence_texture.loadFromFile("../../img/Electric_fence.png"); // Top - polozenie y
    fence_sprite.setTexture(fence_texture);                     // Width - obrot, 1 oznacza pionowo, 0 oznacza poziomo
    frames.emplace_back(sf::IntRect(0, 0, 128, 128));           // Height - brak
    frames.emplace_back(sf::IntRect(128, 0, 128, 128));
    frames.emplace_back(sf::IntRect(256, 0, 128, 128));
    frames.emplace_back(sf::IntRect(0, 128, 128, 128));
    frames.emplace_back(sf::IntRect(128, 128, 128, 128));
    frames.emplace_back(sf::IntRect(256, 128, 128, 128));
    frames.emplace_back(sf::IntRect(0, 256, 128, 128));
    frames.emplace_back(sf::IntRect(128, 256, 128, 128));
    frames.emplace_back(sf::IntRect(256, 256, 128, 128));
    frames.emplace_back(sf::IntRect(0, 384, 128, 128));
    frames.emplace_back(sf::IntRect(128, 384, 128, 128));
    frames.emplace_back(sf::IntRect(256, 384, 128, 128));
    frame_number = 0;
    fence_sprite.setOrigin(64,64);
    fence_sprite.setScale(2,2);
    fence_sprite.setPosition(global_bounds.left, global_bounds.top);
    if (global_bounds.width == 1)
        fence_sprite.setRotation(90);
    slow_factor = 0.4/DifficultyMenu::mnoznik_trud;
    hit_box.setSize(sf::Vector2f(256, 16));
    hit_box.setOrigin(128,8);
    hit_box.setRotation(fence_sprite.getRotation());
    hit_box.setPosition(fence_sprite.getPosition());
    //hit_box.setFillColor(sf::Color::Green);
}

void Electric_fence::draw(sf::RenderWindow &window, float dt) {
    frame_timer += dt;
    if (frame_timer >= 0.1) {
        frame_timer = 0;
        frame_number++;
    }
    fence_sprite.setTextureRect(frames[frame_number%12]);
    //window.draw(hit_box);
    window.draw(fence_sprite);
}

bool Electric_fence::check_collision(sf::FloatRect object_bounds) {
    return hit_box.getGlobalBounds().intersects(object_bounds);
}
