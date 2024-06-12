#include "include/start_menu.h"
#include "include/trud_menu.h"

StartMenu::StartMenu(sf::RenderWindow& window) {
    initialize(window);
}

void StartMenu::initialize(sf::RenderWindow& window) {
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
        return;
    }

    if (!t_logo.loadFromFile(s_logo)) {
        displayErrorWindow("Nie udalo sie zaladowac tekstur");
        return;
    }

    logo.setTexture(t_logo);
    logo.setOrigin(t_logo.getSize().x / 2, 0);
    logo.setPosition(sf::Vector2f(window.getSize().x / 2, 150));

    start.setFont(font);
    start.setString("START");
    start.setCharacterSize(70);
    start.setFillColor(nieaktywny);
    start.setOrigin(start.getLocalBounds().width / 2, start.getLocalBounds().height / 2);
    start.setPosition(sf::Vector2f(window.getSize().x / 2, 450));

    trud.setFont(font);
    trud.setString("POZIOM TRUDNOSCI");
    trud.setCharacterSize(70);
    trud.setFillColor(nieaktywny);
    trud.setOrigin(trud.getLocalBounds().width / 2, trud.getLocalBounds().height / 2);
    trud.setPosition(sf::Vector2f(window.getSize().x / 2, 600));

    pomoc.setFont(font);
    pomoc.setString("POMOC");
    pomoc.setCharacterSize(70);
    pomoc.setFillColor(nieaktywny);
    pomoc.setOrigin(pomoc.getLocalBounds().width / 2, pomoc.getLocalBounds().height / 2);
    pomoc.setPosition(sf::Vector2f(window.getSize().x / 2, 750));
}

void StartMenu::help() {
    sf::RenderWindow helpWindow(sf::VideoMode(600, 400), "Pomoc");
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

    sf::Text helpTitle;
    helpTitle.setFont(font);
    helpTitle.setString("POMOC:");
    helpTitle.setCharacterSize(100);
    helpTitle.setFillColor(sf::Color::Green);
    helpTitle.setPosition(50, 30);

    while (helpWindow.isOpen()) {
        sf::Event event;
        while (helpWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                helpWindow.close();
            }
        }

        helpWindow.clear(sf::Color::Black);
        helpWindow.draw(helpText);
        helpWindow.draw(helpTitle);
        helpWindow.display();
    }
}

void StartMenu::run(sf::RenderWindow& window) {
    while (window.isOpen() && kontynuj) {
        handleEvents(window);

        window.clear(sf::Color::Black);
        window.draw(logo);
        window.draw(start);
        window.draw(trud);
        window.draw(pomoc);
        window.display();
    }
}

void StartMenu::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (start.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    kontynuj = false;
                    return;
                }

                if (trud.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    DifficultyMenu trud_menu_window(window);
                    trud_menu_window.run(window);
                }

                if (pomoc.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    help();
                }
            }
        }
    }

    animacja(start,window);
    animacja(trud,window);
    animacja(pomoc,window);
}
