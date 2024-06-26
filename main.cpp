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
#include "include/shop_menu.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include "include/Bullet.h"
#include "include/Guns.h"
#include "include/Electric_fence.h"
#include <fstream>
#include <sstream>
#include "include/End_gate.h"
#include "windows.h"
#include "include/koniec.h"

sf::RenderWindow window(sf::VideoMode(1920, 1080), "3098 PIXTLE", sf::Style::Close);

bool poziom(int poziom);

int main() {
    try {
        // ladowanie ikony
        sf::Image icon;
        if (!icon.loadFromFile("../../img/logo.png")) {
            return -1; // Blad przy ladowaniu ikony
        }

        // ustawienie ikony
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        int level_number = 1; // poziom 1
        while (window.isOpen()) {
            if (level_number >= 3) { // warunek przejscia calej gry
                std::cout << "wygrales!!!";
                return 0; // wyjscie
            }
            srand((time(NULL))); // zeby monstery sie pojawialy w losowych miejscach
            window.setFramerateLimit(60); // ustawienie stalego limitu klatek/s

            StartMenu st(window);
            st.run(window);

            if(window.isOpen() && poziom(level_number)) // uruchamia poziom
                level_number++; // jesli poziom zostal pokonany, przechodzi na nastepny poziom


        }
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception occurred!" << std::endl;
    }

    return 0;
}

bool poziom(int poziom) {
    try {
        // deklaracje
        Character player;
        Guns gun;
        std::vector<Monster> monsters;
        End_gate end_gate;

        for (int i = 0; i < 30*poziom; i++) {
            monsters.emplace_back(Monster());
        }

        Skills* dash = new Dash(1000,player.player_sprite,player.hit_box);
        Skills* teleport = new Chronobreak(player.player_sprite, player.hit_box, &player.hp);
        Skills* fireball = new Fireball(player.player_sprite, &monsters);
        Skills* zap = new Zap(player.player_sprite, &monsters);

        ShopMenu sklep(window,gun,player,dash,teleport,fireball,zap);
        sklep.run(window);

        player.setPosition(sf::Vector2f(128, 540));

        std::vector<Electric_fence> walls;
        // wczytywanie rozlozenia scian dla poziomu z pliku .txt
        if (poziom >= 3) {
            std::cout << "nie można wczytać pliku" << std::endl;
            return 0;
        }
        std::string file_name = "../../level/" + std::to_string(poziom) + ".txt";
        std::ifstream level_file(file_name);
        if (!level_file.is_open()) {
            std::cout << "nie mozna otworzyc pliku" << std::endl;
            return 0;
        }

        std::string line;
        while (std::getline(level_file, line)) {
            std::stringstream ss(line);
            std::string number;
            std::getline(ss, number, ',');
            int x = std::stoi(number);
            std::getline(ss, number, ',');
            int y = std::stoi(number);
            std::getline(ss, number, ',');
            int if_rotate = std::stoi(number);
             walls.emplace_back(sf::FloatRect(x, y, if_rotate, 0));
        }

        level_file.close(); // Zamknięcie pliku

        std::vector<Bullet> bullets;
        sf::Clock clock;

        sf::Font font;
        if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
            std::cout << "Nie można wczytać czcionki!" << std::endl;
            return -1;
        }

        // wyswietlanie aktualnego zdrowia gracza
        sf::Text healthText;
        healthText.setFont(font);
        healthText.setCharacterSize(24);
        healthText.setFillColor(sf::Color::Red);
        healthText.setPosition(window.getSize().x - 150, 10);

        while (window.isOpen()) { // glowna petla programu
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    exit(0);
                }
            }

            // czas i zmienne dla jednej klatki
            sf::Time elapsed = clock.restart();
            float dt = elapsed.asSeconds(); // czas miedzy klatkami
            sf::Vector2f mouse_xy(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            gun.increse_timer(dt); // roznica czasu pomiedzy strzalami

            // poruszanie sie
            player.top = 0;  // resetujemy wartości na 0 przed sprawdzeniem
            player.right = 0;
            player.is_walking = false;

            // gracz nie moze sie poruszac w trakcie animacji spella, ktory dziala na jego polozenie
            // na pierwszy slot nie trafi fireball i zap
            if ((player.skill_first_slot->name == "DASH" && player.skill_first_slot->animation_time <= 0)
                || (player.skill_first_slot->name == "TELEPORT" && player.skill_first_slot->animation_time <= 0)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 0) {
                    player.top = -1;
                    player.is_walking = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y < window.getSize().y) {
                    player.top = 1;
                    player.is_walking = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > 0) {
                    player.right = -1;
                    player.is_walking = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < window.getSize().x) {
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
                player.skill_first_slot->change_cooldown(dt); // zmiana czasu odnowienia
            if (player.skill_second_slot != nullptr)
                player.skill_second_slot->change_cooldown(dt); // zmiana czasu odnowienia

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

            // interakcja scian z graczem i potworami
            for (size_t i = 0; i < walls.size(); i++) {
                if (walls[i].check_collision(player.hit_box.getGlobalBounds())) {
                    player.slow_factor = walls[i].slow_factor;
                    player.slow_timer = 2.0f;
                }
                for (auto &monster : monsters) {
                    if (walls[i].check_collision(monster.hit_box.getGlobalBounds())) {
                        monster.slow_factor = walls[i].slow_factor;
                        monster.slow_timer = 2.0f;
                    }
                }
            }

            // interakcja pociskow ze scianami i potworami
            for (size_t i = 0; i < bullets.size(); i++) {
                bullets[i].move_(dt);
                if (!bullets[i].is_bullet_in())
                    bullets.erase(bullets.begin() + i);
                for (auto &wall : walls) {
                    if (bullets[i].check_collision(wall.hit_box.getGlobalBounds())) {
                        bullets.erase(bullets.begin() + i);
                        break;
                    }
                }
                for (auto &monster : monsters) {
                    if (bullets[i].check_collision(monster.hit_box.getGlobalBounds()) && monster.hp > 0) {
                        monster.hp -= gun.damage;
                        bullets.erase(bullets.begin() + i);
                        break;  // Wychodzimy z pętli, aby uniknąć problemów z iteratorami
                    }
                }
            }

            // obsluga jesli gracz ma mniej niz 0 hp - pozniej zwraca wartosc false funkcji poziom()
            if (player.hp <= 0) {
                std::cout << "gracz ma mniej niz 0 hp\n";
                Koniec koniec(false);
                koniec.run(window);
                return 0;
            }
            if (end_gate.check_collision(player.player_sprite.getGlobalBounds())) {
                end_gate.timer += dt;
                if (end_gate.timer > end_gate.time) {
                    Koniec koniec(true);
                    koniec.run(window);
                    return 1;
                }
            }

            healthText.setString("HP: " + std::to_string(player.hp));

            // renderowanie
            window.clear();

            for (auto &bullet : bullets)
                window.draw(bullet);

            for (auto it = monsters.begin(); it != monsters.end();) {
                it->reduce_stun(dt);
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

            window.draw(end_gate);

            player.draw(window, dt, mouse_xy);

            for (auto &wall : walls)
                wall.draw(window,dt);

            window.draw(healthText);

            window.display();
        }

    } catch (const std::exception &e) {
        std::cout << "Exception in poziom: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception occurred in poziom!" << std::endl;
    }

    return false;
}
