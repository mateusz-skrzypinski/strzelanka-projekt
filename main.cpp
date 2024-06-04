#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "include/Character.h"
#include "include/Monster.h"
#include "include/Zap.h"
#include "include/Skills.h"
#include "include/Fireball.h"
#include <iostream>
#include <vector>
#include <ctime>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

void start();   //menu startu

bool poziom(); //zwraca true jak gracz przejdzie false jak umrze

int main() {
    srand((time(NULL)));
    window.setFramerateLimit(60);

    start();

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
    player.skill_second_slot = new Fireball(player.player_shape, &monsters);

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
        // tylko do testowania      pozniej raczej metoda klasy
        for (auto monster = monsters.begin(); monster != monsters.end(); ) {
            monster->reduce_stun(dt);
            monster->draw(window, dt);
            if (monster->hp <= 0) {
                monster = monsters.erase(monster); // erase zwraca następny ważny iterator
            } else {
                monster++; // inkrementacja iteratora tylko, gdy nie usuwamy elementu
            }              // inaczej program zaczyna korzystać z z usuniętych elementów
        }

        player.skill_second_slot->draw(window, dt);
        player.draw(window);

        window.display();
    }

    return true;
}

void start()
{
    sf::Font menu_czcionka;
    menu_czcionka.loadFromFile("../../font/Honk-Regular.ttf");

    window.clear(sf::Color::Black);
    while(window.isOpen()){
        window.clear(sf::Color::Black);
        sf::Texture t_logo;
        t_logo.loadFromFile("../../img/logo.png");
        sf::Sprite logo(t_logo);
        logo.setOrigin(t_logo.getSize().x/2,0);
        logo.setPosition(sf::Vector2f(window.getSize().x/2,150));

        sf::Text start("START",menu_czcionka,5);
        start.setCharacterSize(40);
        start.setFillColor(sf::Color::Green);
        start.setPosition(window.getSize().x/2-150,400);

        sf::Text trud("POZIOM TRUDNOSCI",menu_czcionka,5);
        trud.setCharacterSize(40);
        trud.setFillColor(sf::Color::Green);
        trud.setPosition(window.getSize().x/2-300,600);

        window.draw(logo);
        window.draw(start);
        window.draw(trud);

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                // Close window button clicked.
                window.close();
            }
        }

        // Draw here.
        window.display();
    }
}
