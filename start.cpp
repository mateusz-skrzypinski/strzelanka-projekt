#include "include/start.h"

void Start::displayErrorWindow(const std::string& errorMsg) {
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

Start::Start() {
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
        //obsluz blad
        return;
    }

    if (!t_logo.loadFromFile(s_logo) ||
        !t_start.loadFromFile(s_start) ||
        !t_trud.loadFromFile(s_trud) ||
        !t_pomoc.loadFromFile(s_pomoc)) {
        displayErrorWindow("Nie udalo sie zaladowac tekstur");
        return;
    }

    logo.setTexture(t_logo);
    logo.setOrigin(t_logo.getSize().x / 2, 0);
    logo.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, 150));

    start.setTexture(t_start);
    start.setOrigin(t_start.getSize().x / 2, 0);
    start.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, 450));

    trud.setTexture(t_trud);
    trud.setOrigin(t_trud.getSize().x / 2, 0);
    trud.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, 650));

    pomoc.setTexture(t_pomoc);
    pomoc.setOrigin(t_pomoc.getSize().x / 2, 0);
    pomoc.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, 850));
}

void Start::run(sf::RenderWindow& window) {
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

                    if (pomoc.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        help();
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

void Start::help() {
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

    sf::Text help;
    help.setFont(font);
    help.setString("POMOC:");
    help.setCharacterSize(100);
    help.setFillColor(sf::Color::Green);
    help.setPosition(50, 30);

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
