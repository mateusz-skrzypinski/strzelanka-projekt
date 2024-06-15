#include "include/koniec.h"
#include <iostream>

Koniec::Koniec(bool arg_wygrana) { // konstruktor, kótry przyjmuje wartość, true lub false
    wygrana = arg_wygrana;         // true - gdy gracz wygra poziom
    if (wygrana)                   // false - gdy gracz przegra poziom
        tekstura.loadFromFile(wygrano); // jesli wygra, to laduje teksture dla wygranego poziomu
    else
        tekstura.loadFromFile(przegrana); // jesli przegra, laduje teksture dla przegranego poziomu

    tlo.setTexture(tekstura); // ustawienie tekstury dla sprite "tlo"
    tlo.setPosition(0, 0); // ustawienie pozycji początkowej - tlo i wyswietlane okno jest tego samego rozmiaru,
}                          // wiec nie trzeba tego dostosowywac

void Koniec::run(sf::RenderWindow& arg_window) { // funkcja tworzaca nowe okno z informacja, czy gracz wygral, cz przegral i pozwala mu zagrac ponownie
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "3098 PIXTLE"); // ustawienie nowego okna
    sf::Image icon; // zdefiniowanie loga w nowym oknie
    icon.loadFromFile("../../img/logo.png"); // ladowanie tekstury loga
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // ustawienie tekstury jako logo

    sf::Font font; // definicja uzywanej czcionki
    font.loadFromFile("../../font/Honk-Regular.ttf"); // zaladowanie czcionki z pliku
    sf::Text play_button("", font, 70); // definicja tekstow - przyciskow dla zagraj ponownie / przej do nastepnego poziomu
    sf::Text message("", font, 70); // definicja tekstow - przyciskow dla wygrana / Nie udalo sie, sprobuj ponownie

    play_button.setOrigin(play_button.getGlobalBounds().width / 2, play_button.getGlobalBounds().height / 2); // ustawienie punktu odniesia na srodek dla obydwu przyciskow
    message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2 - 300);
    play_button.setPosition(0, 400); // ustawienie przyciskow w oknie dla przyciskow "Graj" i "Powiadomienie"
    message.setPosition(400, -150);
    if (wygrana) { // wykorzystuje przekazany argument do konstruktora i na tej podstawie wybiera, jakie powinny byc teksty przyciskow
        play_button.setString("Przejdz do nastepnego poziomu"); // przyciski dla wygranej
        message.setString("Wygrana!");
    }
    else {
        play_button.setString("Zagraj ponownie"); // przyciski dla przegranej
        message.setString("Nie udalo sie, sprobuj ponownie");
    }

    while (window.isOpen()) { // jezeli okno jest otwarte
        sf::Event event;      // to sprawdza dwie rzeczy
        while (window.pollEvent(event)) { // 1. czy gracz zamyka okno
            if (event.type == sf::Event::Closed) {
                window.close(); // zamyka otawrte okno
                return; // wychodzi z metody
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pobranie wartosci x,y gdzie znajduje sie myszka
            if (event.type == sf::Event::MouseButtonPressed) { // nacisniecie na przycisk
                if (play_button.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // sprawdzenie, czy gracz nacisnal na napis
                    window.close(); // powoduje zamkniecie okna
                    return; // i wyjscie z metody
                }
            }
            animacja(play_button, window); // metoda klasy bazowej - definicja w "menu.cpp"
                                           // metoda ta sprawdza, czy myszka najechala na przycisk w formie tekstu i zmiena jego kolor jesli tak
            window.draw(tlo); // renderowanie tla
            window.draw(play_button); // renderowanie przyciskow
            window.draw(message);
            window.display();
        }
    }
}

void Koniec::handleEvents(sf::RenderWindow& window) {} // brak definicji dla tej klasy pochodnej po klasie Menu
