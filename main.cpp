#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "include/Character.h"
#include "include/Monster.h"
#include "include/Zap.h"
#include "include/Skills.h"
#include "include/Fireball.h"
#include "include/start.h"
#include <vector>
#include <ctime>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

void start();   //menu startu

bool poziom(); //zwraca true jak gracz przejdzie false jak umrze

void pomoc(); //wyswietla ekran pomocy

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
    sf::Font font;
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
        return;
    }

    // Ładowanie tekstur raz na początku
    sf::Texture t_logo, t_start, t_trud, t_pomoc;
    if (!t_logo.loadFromFile("../../img/logo.png") ||
        !t_start.loadFromFile("../../img/start.png") ||
        !t_trud.loadFromFile("../../img/poziom_trud.png") ||
        !t_pomoc.loadFromFile("../../img/pomoc.png")) {

        sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "Błąd");
        sf::Font font;
        if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
            // Obsługa błędów ładowania czcionki
            return;
        }

        sf::Text errorMsg("Nie udalo sie zaladowac tekstur", font, 20);
        errorMsg.setFillColor(sf::Color::Red);
        errorMsg.setPosition(50, 80);

        while (errorWindow.isOpen()) {
            sf::Event event;
            while (errorWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    errorWindow.close();
                    exit(-1);
                }
            }

            errorWindow.clear();
            errorWindow.draw(errorMsg);
            errorWindow.display();
        }
    }

    sf::Sprite logo(t_logo);
    logo.setOrigin(t_logo.getSize().x / 2, 0);
    logo.setPosition(sf::Vector2f(window.getSize().x / 2, 150));

    sf::Sprite start(t_start);
    start.setOrigin(t_start.getSize().x / 2, 0);
    start.setPosition(sf::Vector2f(window.getSize().x / 2, 450));

    sf::Sprite trud(t_trud);
    trud.setOrigin(t_trud.getSize().x / 2, 0);
    trud.setPosition(sf::Vector2f(window.getSize().x / 2, 650));

    sf::Sprite pomoc(t_pomoc);
    pomoc.setOrigin(t_pomoc.getSize().x / 2, 0);
    pomoc.setPosition(sf::Vector2f(window.getSize().x/2, 850));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Sprawdzanie kliknięcia myszą
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Sprawdzenie, czy kliknięto w przycisk "Start"
                    if (start.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        return;
                    }

                    // Sprawdzenie, czy kliknięto w przycisk "Poziom trudności"
                    if (trud.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Tutaj wyświetlenie menu poziomu trudności
                    }

                    if (pomoc.getGlobalBounds().contains(mousePos.x,mousePos.y)) {
                        ::pomoc();
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(logo);
        window.draw(start);
        window.draw(trud);
        window.draw(pomoc);

        window.display();
    }
}

void pomoc() {
    sf::RenderWindow helpWindow(sf::VideoMode(600, 400), "Pomoc");
    sf::Font font;
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
        return;
    }

    sf::Text helpText;
    helpText.setFont(font);
    helpText.setString(
        "WASD - poruszanie sie postacia\n"
        "Q - umiejetnosc zwiazana z zadawaniem obrazen\n"
        "E - umiejetnosc zwiazana z przemieszczaniem sie\n"
        "Lewy przycisk myszy - strzal z broni"
        );
    helpText.setCharacterSize(20);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(50, 150);

    sf::Text help;
    help.setFont(font);
    help.setString("POMOC:");
    help.setCharacterSize(100);
    help.setFillColor(sf::Color::Green);
    help.setPosition(50,30);

    while (helpWindow.isOpen()) {
        sf::Event event;
        while (helpWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                helpWindow.close();
            }
        }

        helpWindow.clear(sf::Color::Black);
        helpWindow.draw(helpText);
        helpWindow.draw(help);
        helpWindow.display();
    }
}
