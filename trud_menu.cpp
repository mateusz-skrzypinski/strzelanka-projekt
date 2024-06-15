#include "include/trud_menu.h"

double DifficultyMenu::mnoznik_trud = 1.0f; // definicja statycznej zmiennej klasy DifficultyMenu

DifficultyMenu::DifficultyMenu(sf::RenderWindow& window) { // konstruktor przechwytuje tylko okno do rysowania
    initialize(window); // uruchami ametode, ktora deifniuje przyciski w formacie tekstu
}

void DifficultyMenu::initialize(sf::RenderWindow& window) { // metoda definujaca przyciski w formacie tekstu
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) { // proba zaladowania czcionki
        displayErrorWindow("Nie mozna zaladowac czcionki"); // jesli sie nie powiedzie to uruchamiana jest metoda z oknem niepowodzenia z komunikatem "Nie udalo sie zaladowac czcionki"
        return; // wychodzi z meotdy initialize
    }
    zaladuj_tlo(); // laduje tlo, metoda klasy bazowej, definicja w pliku "menu.cpp"

    // deklaracje przyciskow znajduja sie w klasie DifficultyMenu w pliku "trud_menu.h"

    easy.setFont(font); // przypisanie czcionki do tekstu
    easy.setString("Latwy"); // przypisanie wyswietlanego przez przycisk tekstu
    easy.setCharacterSize(70); // przyspianie wielkosci czcionki do tekstu
    easy.setFillColor(nieaktywny); // ustawienie jej domyslnego koloru zdefiniowanego bezposrednio w klasie bazowej "menu.h"
    easy.setOrigin(easy.getLocalBounds().width / 2, easy.getLocalBounds().height / 2); // ustawienie innego punktu odniesienia
    easy.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 150)); // ustawienie poczycji tekstu na oknie wzdgledem window

    medium.setFont(font); // przypisanie czcionki do tekstu
    medium.setString("Sredni"); // przypisanie wyswietlanego przez przycisk tekstu
    medium.setCharacterSize(70); // przyspianie wielkosci czcionki do tekstu
    medium.setFillColor(nieaktywny); // ustawienie jej domyslnego koloru zdefiniowanego bezposrednio w klasie bazowej "menu.h"
    medium.setOrigin(medium.getLocalBounds().width / 2, medium.getLocalBounds().height / 2); // ustawienie innego punktu odniesienia
    medium.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2)); // ustawienie poczycji tekstu na oknie wzgledem window

    hard.setFont(font); // przypisanie czcionki do tekstu
    hard.setString("Trudny"); // przypisanie wyswietlanego przez przycisk tekstu
    hard.setCharacterSize(70); // przyspianie wielkosci czcionki do tekstu
    hard.setFillColor(nieaktywny); // ustawienie jej domyslnego koloru zdefiniowanego bezposrednio w klasie bazowej "menu.h"
    hard.setOrigin(hard.getLocalBounds().width / 2, hard.getLocalBounds().height / 2); // ustawienie innego punktu odniesienia
    hard.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 150)); // ustawienie poczycji tekstu na oknie wzgledem window
}


void DifficultyMenu::run(sf::RenderWindow& window) { // glowna petla wybory poziomu trudnosci
    mnoznik_trud = 1; // przypisanie domyslnej wartosci rownej 1 - sredni poziom trudnosci
    while (window.isOpen() && kontynuj) { // sprawdzenie, czy okno jest otwarte i flagi kontynuuj
        handleEvents(window); // cala implementacja do zarzadzania przyciskami jest opisana w metodzie handleEvents

        // renderowanie
        window.clear(sf::Color::Black); // czyszczenie okna
        window.draw(tlo); // rysowanie tla
        window.draw(easy); // rysowanie przeyciskow
        window.draw(medium); // rysowanie przeyciskow
        window.draw(hard); // rysowanie przeyciskow
        window.display(); // wyswietlenie
    }
}

void DifficultyMenu::handleEvents(sf::RenderWindow& window) { // metoda z implementacja zarzadzania przyciskami
    sf::Event event; // deklaracja zmiennej event
    while (window.pollEvent(event)) { // jesli window zarejestruje jakies zdarzenie, to:
        if (event.type == sf::Event::Closed) { // 1. jesli gracz chce zamknac okno, to
            window.close(); // zamyka okno
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pobieranie pozycji myszki z okna do sprawdzenia jej pozycji
        if (event.type == sf::Event::MouseButtonPressed) { // 2. jesli gracz nacisnie na lewy przycisk myszy, to sprawdza, czy nie zostal klikniety w jakis przycisk
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (easy.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // wybrano latwy tryb gry
                    mnoznik_trud = 0.7; // zmiana mnoznika na mniejszy, oznacza to, ze przykladowo zdrowie potworow zmniejszy sie o 30%
                    kontynuj = false; // zmiana flagi kontynuuj na flase
                    return; // wychodzi z metody handleEvents
                }

                if (medium.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // wybrano sredni tryb gry
                    mnoznik_trud = 1; // zmiana mnoznika z powrotem na 1, czyli przykladowo zdrowie potworow pozostanie bez zmian
                    kontynuj = false; // zmiana flagi kontunuuj na flase
                    return; // wychodz z metody handleEvents
                }

                if (hard.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // wybrano trudny tryb gry
                    mnoznik_trud = 1.4; // zmiana mnoznika na wiekszy, oznacza to, ze przykladowo zdrowie potworow zwiekszy sie o 40%
                    kontynuj = false; // zmiana flagi kontynuj na false
                    return; // wychozi z metody handleEvents
                }
            }
        }
    }

    // wywolanie dla wszystkich przyciskow metody klasy bazowej dla animacj zmiany koloru, jesli myszka najedzie na przycisk, definicja w "menu.h"
    animacja(easy, window);
    animacja(medium, window);
    animacja(hard, window);
}
