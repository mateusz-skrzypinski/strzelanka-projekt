#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "include/Character.h"
#include <iostream>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

int main() {
    window.setFramerateLimit(60);
    Character player;
    player.setPosition(400, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float speed = 400.0f;
        sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
        float dt = deltaTime.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 0) {
            player.move(sf::Vector2f(0, -speed * dt));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y + player.player_shape.getGlobalBounds().height < window.getSize().y) {
            player.move(sf::Vector2f(0, speed * dt));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > 0) {
            player.move(sf::Vector2f(-speed * dt, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x + player.player_shape.getGlobalBounds().width < window.getSize().x) {
            player.move(sf::Vector2f(speed * dt, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
            player.skill_first_slot->use_skill(sf::Vector2f(mouse_position));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
            player.skill_second_slot->use_skill(sf::Vector2f(mouse_position));
        }
        player.skill_first_slot->change_cooldown(dt);
        player.skill_second_slot->change_cooldown(dt);
        player.hp -= dt;
        std::cout << player.hp << std::endl;
        window.clear();
        player.skill_second_slot->draw(window);
        window.draw(player.player_shape);
        window.display();
    }

    return 0;
}
