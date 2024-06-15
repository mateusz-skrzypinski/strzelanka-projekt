#include "include/start_menu.h"
#include "include/trud_menu.h"

StartMenu::StartMenu(sf::RenderWindow& window) { // konstruktor przechwytuje tylko okno potrzebne do rysowania
    initialize(window); // uruchamia metode, ktora definiuje przyciski w formie tekstu
}

void StartMenu::initialize(sf::RenderWindow& window) { // metoda definiuje przyciski w formie tekstu
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) { // proba zaladowania czcionki
        return; // jesli sie nie powiedzie, to wychodzi z metody
    }

    if (!t_logo.loadFromFile(s_logo)) { // proba zaladowania logo gry
        displayErrorWindow("Nie udalo sie zaladowac tekstur"); // proba nieudana, wiec uruchamie okno niepowodzenia z komunikatem "Nie udalo sie zaladowac tekstur"
        return; // wyjscie z meotdy
    }

    // definicja sprite'a o teksturze loga
    logo.setTexture(t_logo); // przypisanie do sprite tekstury
    logo.setScale(0.25f,0.25f); // ustawienie skali, zeby osiagnac wybrany rerezultat
    logo.setOrigin(t_logo.getSize().x / 2, 0); // ustawienie innego punktu odniesienia
    logo.setPosition(sf::Vector2f(window.getSize().x / 2, 100)); // ustawienie pozycji wyswietlania loga

    // definicja przycisku "START"
    start.setFont(font); // przypisanie czcionki dla przycisku
    start.setString("START"); // przypisanie przyciskowi wyswietlanego tekstu
    start.setCharacterSize(70); // przypisanie przyciskowi wielkosci czcionki
    start.setFillColor(nieaktywny); // przypisanie domyslnego koloru jako nieaktywnego, zdefiniowanego bezposrednio w klasie Menu w "menu.h"
    start.setOrigin(start.getLocalBounds().width / 2, start.getLocalBounds().height / 2); // ustawienie innego pnktu odniesienia
    start.setPosition(sf::Vector2f(window.getSize().x / 2, 450)); // ustawienie pozycji wyswietlania przycisku na ekranie

    // definicja przyciskiu "POZIOM TRUDNOSCI"
    trud.setFont(font); // przypisanie czcionki dla przycisku
    trud.setString("POZIOM TRUDNOSCI"); // przypisanie przyciskowi wyswietlanego tekstu
    trud.setCharacterSize(70); // przypisanie przyciskowi wielkosci czcionki
    trud.setFillColor(nieaktywny); // przypisanie domyslnego koloru jako nieaktywnego, zdefiniowanego bezposrednio w klasie Menu w "menu.h"
    trud.setOrigin(trud.getLocalBounds().width / 2, trud.getLocalBounds().height / 2); // ustawienie innego pnktu odniesienia
    trud.setPosition(sf::Vector2f(window.getSize().x / 2, 600)); // ustawienie pozycji wyswietlania przycisku na ekranie

    // definicja przycisku "POMOC"
    pomoc.setFont(font); // przypisanie czcionki dla przycisku
    pomoc.setString("POMOC"); // przypisanie przyciskowi wyswietlanego tekstu
    pomoc.setCharacterSize(70); // przypisanie przyciskowi wielkosci czcionki
    pomoc.setFillColor(nieaktywny); // przypisanie domyslnego koloru jako nieaktywnego, zdefiniowanego bezposrednio w klasie Menu w "menu.h"
    pomoc.setOrigin(pomoc.getLocalBounds().width / 2, pomoc.getLocalBounds().height / 2); // ustawienie innego pnktu odniesienia
    pomoc.setPosition(sf::Vector2f(window.getSize().x / 2, 750)); // ustawienie pozycji wyswietlania przycisku na ekranie
}

void StartMenu::help() { // metoda tworzaca nowe okno po nacisnieciu na przycisk "POMOC"
    sf::RenderWindow helpWindow(sf::VideoMode(600, 400), "Pomoc"); // stworzenie nowego okna
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) { // proba odczytania z pliku czcionki
        return; //  jesli proba jest nieudana, wychodzi z metody help
    }

    sf::Text helpText; // deklaracja wyswietlanego tekstu
    helpText.setFont(font); //przypisanie do tekstu czcionki
    helpText.setString( // ustawienie wyswietlanego tekstu
        "WASD - poruszanie sie postacia\n"
        "Q - umiejetnosc zwiazana z zadawaniem obrazen\n"
        "E - umiejetnosc zwiazana z przemieszczaniem sie\n"
        "Lewy przycisk myszy - strzal z broni"
        );
    helpText.setCharacterSize(20); // ustawienie wiekosi czcionki dla tekstu
    helpText.setFillColor(sf::Color::White); // ustawienie koloru czcionki
    helpText.setPosition(50, 150); // ustawienie pozycji czcionki

    sf::Text helpTitle; // deklaraca naglowka "POMOC:"
    helpTitle.setFont(font); // przypisanie jej czcionki wyswietlanego tekstu
    helpTitle.setString("POMOC:"); // ustawienie jej wyswietlanego naglowka
    helpTitle.setCharacterSize(100); // ustawienie rozmiaru naglowka
    helpTitle.setFillColor(sf::Color::Green); // ustawienie koloru naglowka
    helpTitle.setPosition(50, 30); // ustawienie pozycji naglowka

    while (helpWindow.isOpen()) { // sprawdzenie czy okno pomoc jest otwarte
        sf::Event event;
        while (helpWindow.pollEvent(event)) { // obsluga zdarzen w oknie pomocy
            if (event.type == sf::Event::Closed) { // jesli gracz nacisnie na zamkniecie okna
                helpWindow.close(); // zamyka okno
            }
        }

        // renderowanie
        helpWindow.clear(sf::Color::Black);  // czysci okno
        helpWindow.draw(helpText); // wyswietla na oknie tekst pomocy
        helpWindow.draw(helpTitle); // wyswietla na oknie naglowek pomocy
        helpWindow.display(); // wyswietlenie okna
    }
}

void StartMenu::run(sf::RenderWindow& window) { // glowna pelta programu dla menu startowego
    while (window.isOpen() && kontynuj) { // petla programu dopoki okno jest otwarte
        handleEvents(window); // cala implementacja do zarzadzania przyciskami jest opisana w metodzie handleEvents

        window.clear(sf::Color::Black);
        window.draw(logo);
        window.draw(start);
        window.draw(trud);
        window.draw(pomoc);
        window.display();
    }
}

void StartMenu::handleEvents(sf::RenderWindow& window) { // cala implementacja do zarzadzania przyciskami jest opisana w metodzie handleEvents
    sf::Event event; // deklaracja zmiennej Event
    while (window.pollEvent(event)) { // jesli window zarejestruje jakies zdarzenie, to:
        if (event.type == sf::Event::Closed) { // 1. jesli gracz chce zamknac okno, to
            window.close(); // zamyka okno
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pobiera pozycje myszki z okna
        if (event.type == sf::Event::MouseButtonPressed) { // 2. jesli gracz nacisnie na lewy przycisk myszy, to sprawdza, czy nie zostal klikniety w jakis przycisk
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (start.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacisnieto przycisk do zaczecia programu
                    kontynuj = false; // ustawienie flagi kontynuuj na false
                    return; // wychodzi z metody
                }

                if (trud.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacienieto przycisk do wyboru poziomu trudnosci
                    DifficultyMenu trud_menu_window(window); // uruchamia konstruktor klasy DifficultyMenu i inicjalizuje przyciski w wyborze trudnosci
                    trud_menu_window.run(window); // uruchamia glowna petle klasy DifficultyMenu
                }

                if (pomoc.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacisnieto przycisk do pomocy
                    help(); // uruchamia metode do wyswietlania pomocy
                }
            }
        }
    }

    // wywolanie dla wszystkich przyciskow metody klasy bazowej dla animacji zmiany koloru jesli myszka najedzie na przycisk, definicja w "menu.h"
    animacja(start,window);
    animacja(trud,window);
    animacja(pomoc,window);
}
