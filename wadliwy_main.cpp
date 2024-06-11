#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "include/Character.h"
#include "include/Monster.h"
#include "include/Zap.h"
#include "include/Skills.h"
#include "include/Fireball.h"
#include "include/start.h"
#include "include/Bullet.h"
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

bool poziom(); //zwraca true jak gracz przejdzie false jak umrze
void bullet_interaction(std::vector<Bullet> &bullets, std::vector<Monster> &monsters, float dt);

int main() {
    srand((time(NULL)));
    window.setFramerateLimit(60);

    Start st;
    st.run(window);

    poziom();

    return 0;
}

bool poziom()
{
    Character player;
    player.setPosition(sf::Vector2f(400, 300));
    std::vector<Monster> monsters;
    for (int i = 0; i < 5; i++) {
        monsters.emplace_back(Monster());
    }
    player.skill_second_slot = new Fireball(player.player_sprite, &monsters);

    sf::Clock clock;

    float timer = 0.0f; // inicjalizacja timera
    sf::Vector2f mouse_position;
    sf::Vector2f character_position;
    sf::Vector2f aim_direction;
    double norm;
    sf::Vector2f normalized_aim_vector;
    std::vector<Bullet> bullets; // to wszystko później gdzie indziej

    while (window.isOpen()) {
        std::cout << "start of while loop" <<std::endl;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 0) {
            player.top = -1;
            player.is_walking = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y + player.player_sprite.getGlobalBounds().height < window.getSize().y) {
            player.top = 1;
            player.is_walking = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > 0) {
            player.right = -1;
            player.is_walking = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x + player.player_sprite.getGlobalBounds().width < window.getSize().x) {
            player.right = 1;
            player.is_walking = true;
        }
        std::cout << "before character move" <<std::endl;
        player.move(sf::Vector2f(player.right * player.speed * dt, player.top * player.speed * dt));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && player.skill_first_slot != nullptr) {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
            player.skill_first_slot->use_skill(static_cast<sf::Vector2f>(mouse_position));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && player.skill_second_slot != nullptr) {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
            player.skill_second_slot->use_skill(static_cast<sf::Vector2f>(mouse_position));
        }

        timer += dt;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            player.is_shooting = true;
            mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
            character_position = sf::Vector2f(player.player_sprite.getPosition());
            aim_direction = mouse_position - character_position;
            norm = sqrt(pow(aim_direction.x, 2) + pow(aim_direction.y, 2));
            normalized_aim_vector = sf::Vector2f(aim_direction.x / norm, aim_direction.y / norm);
            Bullet bullet(normalized_aim_vector, player);
            bullet.shoot_bullet();
            bullets.emplace_back(bullet);
            std::cout << "Bullet added to vector" << std::endl;
        }

        bullet_interaction(bullets, monsters, dt);

        window.clear();

        if (player.skill_first_slot != nullptr) {
            player.skill_first_slot->change_cooldown(dt);
            player.skill_first_slot->draw(window, dt);
        }
        if (player.skill_second_slot != nullptr) {
            player.skill_second_slot->change_cooldown(dt);
            player.skill_second_slot->draw(window, dt);
        }

        for (auto &bullet : bullets) {
            std::cout << "bullet has been drawn" << std::endl;
            window.draw(bullet);
        }

        for (auto monster = monsters.begin(); monster != monsters.end(); ) {
            monster->reduce_stun(dt);
            monster->draw(window, dt, player.getPosition());
            if (monster->dying_time <= 0) {
                monster = monsters.erase(monster); // erase zwraca następny ważny iterator
            } else {
                monster++; // inkrementacja iteratora tylko, gdy nie usuwamy elementu
            }              // inaczej program zaczyna korzystać z z usuniętych elementów
        }
        player.draw(window, dt, sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));
        window.display();
    }

    return true;
}

void bullet_interaction(std::vector<Bullet> &bullets, std::vector<Monster>& monsters, float dt) {
    std::cout << bullets.size() << std::endl;
    if (bullets.size() != 0) {
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].move_(dt);
            if (!bullets[i].is_bullet_in())
                bullets.erase(bullets.begin() + i);
            for (size_t j = 0; j < monsters.size(); j++) {
                if (bullets[i].check_collision(monsters[j])) {
                    monsters[j].hp -= bullets[j].bullet_damage;
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
    }
}
