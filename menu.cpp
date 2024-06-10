#include "include/menu.h"

void Menu::animacja(sf::Text& t, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (t.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        t.setFillColor(aktywny);
    } else {
        t.setFillColor(nieaktywny);
    }
}

void Menu::displayErrorWindow(const std::string& errorMsg) {
    sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "Blad");
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
        return;
    }

    sf::Text errorText(errorMsg, font, 20);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(50, 80);

    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                errorWindow.close();
                exit(-1);
            }
        }

        errorWindow.clear();
        errorWindow.draw(errorText);
        errorWindow.display();
    }
}
