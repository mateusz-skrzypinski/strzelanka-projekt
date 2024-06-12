#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "include/Character.h"
#include "include/Monster.h"
#include "include/Zap.h"
#include "include/start_menu.h"
#include "include/Skills.h"
#include "include/Fireball.h"
#include "include/Dash.h"
#include "include/Chronobreak.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include "include/Bullet.h"
#include "include/Guns.h"

sf::RenderWindow window(sf::VideoMode(1920, 1080), "my window", sf::Style::Close);

bool poziom();

int main() {
    try {
        srand((time(NULL)));
        window.setFramerateLimit(60);

        StartMenu st(window);
        st.run(window);

        poziom();
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception occurred!" << std::endl;
    }

    return 0;
}

bool poziom() {
    try {
        // deklaracje
        Character player;
        Guns gun;
        player.setPosition(sf::Vector2f(400, 300));

        player.skill_first_slot = new Dash(1000, player.player_sprite, player.hit_box);
        player.name_of_skill = "Dash"; // bardzo ważne - pamietaj przy tworzeniu sklepu
        // player.skill_first_slot = new Chronobreak(player.player_sprite, player.hit_box, &player.hp);
        // player.name_of_skill = "Teleport"; // bardzo ważne - plamietaj przy tworzeniu sklepu

        std::vector<Monster> monsters;
        for (int i = 0; i < 5; i++) {
            monsters.emplace_back(Monster());
        }
        std::vector<Bullet> bullets;
        sf::Clock clock;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // czas i zmienne dla jednej klatki
            sf::Time elapsed = clock.restart();
            float dt = elapsed.asSeconds();
            sf::Vector2f mouse_xy(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            gun.increse_timer(dt);

            // poruszanie sie
            player.top = 0;  // Resetujemy wartości na 0 przed sprawdzeniem
            player.right = 0;
            player.is_walking = false;

            if ((player.name_of_skill == "Dash" && player.skill_first_slot->animation_time <= 0)
                || (player.name_of_skill == "Teleport" && player.skill_first_slot->animation_time <= 0)) {
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
                player.move(sf::Vector2f(player.right * player.speed * dt, player.top * player.speed * dt));
            }

            // spelle
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && player.skill_first_slot != nullptr)
                player.skill_first_slot->use_skill(mouse_xy);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && player.skill_second_slot != nullptr)
                player.skill_second_slot->use_skill(mouse_xy);
            if (player.skill_first_slot != nullptr)
                player.skill_first_slot->change_cooldown(dt);
            if (player.skill_second_slot != nullptr)
                player.skill_second_slot->change_cooldown(dt);

            // strzelanie
            if ((player.name_of_skill == "Teleport" && player.skill_first_slot->animation_time <= 0) || player.name_of_skill != "Teleport") {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (gun.last_bullet_timer > gun.fire_rate) {
                        sf::Vector2f aim_direction = mouse_xy - player.getPosition();
                        float norm = sqrt(pow(aim_direction.x, 2) + pow(aim_direction.y, 2));
                        aim_direction = aim_direction / norm;
                        Bullet bullet(aim_direction, player.getPosition());
                        bullet.shoot_bullet();
                        bullets.emplace_back(bullet);
                        gun.last_bullet_timer = 0;
                    }
                    player.is_shooting = true;
                }
            }
            for (size_t i = 0; i < bullets.size(); i++) {
                bullets[i].move_(dt);
                if (!bullets[i].is_bullet_in())
                    bullets.erase(bullets.begin() + i);
                for (auto &monster : monsters) {
                    if (bullets[i].check_collision(monster) && monster.hp > 0) {
                        monster.hp -= gun.damage;
                        bullets.erase(bullets.begin() + i);
                        break;  // Wychodzimy z pętli, aby uniknąć problemów z iteratorami
                    }
                }
            }

            // obsluga jesli gracz ma mniej niz 0 hp - pozniej zwraca wartosc false funkcji poziom()
            if (player.hp <= 0)
                std::cout << "gracz ma mniej niz 0 hp\n";

            // renderowanie
            window.clear();

            for (auto &bullet : bullets)
                window.draw(bullet);

            for (auto it = monsters.begin(); it != monsters.end();) {
                if (it->hp > 0 && it->check_collision(player.hit_box.getGlobalBounds())) {
                    player.hp -= it->damage;
                }
                it->draw(window, dt, player.getPosition());
                if (it->dying_time <= 0.0f) {
                    it = monsters.erase(it);
                } else {
                    ++it;
                }
            }

            if (player.skill_first_slot != nullptr)
                player.skill_first_slot->draw(window, dt);
            if (player.skill_second_slot != nullptr)
                player.skill_second_slot->draw(window, dt);

            player.draw(window, dt, mouse_xy);

            window.display();
        }

    } catch (const std::exception &e) {
        std::cout << "Exception in poziom: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception occurred in poziom!" << std::endl;
    }

    return false;
}
