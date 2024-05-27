#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "include/Character.h"
#include "include/Monster.h"
#include "include/Zap.h"
#include "include/Skills.h"
#include <iostream>
#include <vector>
#include <ctime>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

int main() {
    srand((time(NULL)));
    window.setFramerateLimit(60);
    Character player;
    player.setPosition(sf::Vector2f(400, 300));
    std::vector<Monster> monsters;
    for (int i = 0; i < 5; i++) {
        monsters.emplace_back(Monster());
    }
    player.skill_second_slot = new Zap(player.player_shape, &monsters);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();
        float speed = 400.0f;

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
            player.skill_first_slot->use_skill(static_cast<sf::Vector2f>(mouse_position));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
            player.skill_second_slot->use_skill(static_cast<sf::Vector2f>(mouse_position));
        }

        player.skill_first_slot->change_cooldown(dt);
        player.skill_second_slot->change_cooldown(dt);

        window.clear();

        for (auto& monster : monsters) {
            monster.reduce_stun(dt);
            monster.draw(window, dt);
        }

        player.skill_second_slot->draw(window);
        player.draw(window);

        window.display();
    }

    return 0;
}
