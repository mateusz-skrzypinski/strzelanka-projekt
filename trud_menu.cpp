#include "include/trud_menu.h"

double DifficultyMenu::mnoznik_trud = 1.0f;

DifficultyMenu::DifficultyMenu(sf::RenderWindow& window) {
    initialize(window);
}

void DifficultyMenu::initialize(sf::RenderWindow& window) {
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
        displayErrorWindow("Nie mozna zaladowac czcionki");
        return;
    }
    zaladuj_tlo();

    easy.setFont(font);
    easy.setString("Latwy");
    easy.setCharacterSize(70);
    easy.setFillColor(nieaktywny);
    easy.setOrigin(easy.getLocalBounds().width / 2, easy.getLocalBounds().height / 2);
    easy.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 150));

    medium.setFont(font);
    medium.setString("Sredni");
    medium.setCharacterSize(70);
    medium.setFillColor(nieaktywny);
    medium.setOrigin(medium.getLocalBounds().width / 2, medium.getLocalBounds().height / 2);
    medium.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    hard.setFont(font);
    hard.setString("Trudny");
    hard.setCharacterSize(70);
    hard.setFillColor(nieaktywny);
    hard.setOrigin(hard.getLocalBounds().width / 2, hard.getLocalBounds().height / 2);
    hard.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 150));
}


void DifficultyMenu::run(sf::RenderWindow& window) {
    mnoznik_trud = 1;
    while (window.isOpen() && kontynuj) {
        handleEvents(window);

        window.clear(sf::Color::Black);
        window.draw(tlo);
        window.draw(easy);
        window.draw(medium);
        window.draw(hard);
        window.display();
    }
}

void DifficultyMenu::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (easy.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mnoznik_trud = 0.7;
                    kontynuj = false;
                    return;
                }

                if (medium.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mnoznik_trud = 1;
                    kontynuj = false;
                    return;
                }

                if (hard.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    mnoznik_trud = 1.4;
                    kontynuj = false;
                    return;
                }
            }
        }
    }

    animacja(easy, window);
    animacja(medium, window);
    animacja(hard, window);
}
