#include "include/menu.h"

// funckja ta pobiera referencje do prawdziwego obiektu, zeby zmieniac na biezaco jego atrybuty - kolor przycisku
void Menu::animacja(sf::Text& t, sf::RenderWindow& window) { // przekazanie dwoch wartosci - text jako przycisk i okno na ktorym jest wyswietlane
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pobranie z okna polozenia x,y myszki
    if (t.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // sprawdzenie, czy myszka najezdza na napis
        t.setFillColor(aktywny); // zmienia kolor na "aktywny", ktory zostal zdefiniowany na stale w "menu.h"
    } else {
        t.setFillColor(nieaktywny); // zmienia kolor na "nieaktywny", ktory zostal zdefiniowany na stale w "menu.h"
    }
}

void Menu::displayErrorWindow(const std::string& errorMsg) { // funkcja pokazujaca graczowi wystapienie bledu z komnuniakatem o wartosci errorMsg
    sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "Blad"); // stworzenie nowego okna
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) { // jesli nie uda sie zaladowac czcionki -
        return;                                              // - wchodzi z metody
    }

    sf::Text errorText(errorMsg, font, 20); // stworzenie tekstu - powiadomienia
    errorText.setFillColor(sf::Color::Red); // ustawienie jego koloru na czerwony
    errorText.setPosition(50, 80); // ustawienie pozycji w oknie "error window"

    while (errorWindow.isOpen()) { // sprawdzenie czy okno dalej jest otwarte
        sf::Event event; // obsluga zamykania okna
        while (errorWindow.pollEvent(event)) { // jesli okno zostanie zamkniete
            if (event.type == sf::Event::Closed) {
                errorWindow.close(); // zamyka okno
                exit(-1); // i wycodzi z programu z kodem -1
            }
        }

        // renderowanie
        errorWindow.clear();
        errorWindow.draw(errorText); // rysowanie tekstu
        errorWindow.display(); // wyswietlanie na ekranie
    }
}

void Menu::zaladuj_tlo() // funkcja ladujaca tlo z pliku
{
    if(!tlo_tekstura.loadFromFile(s_tlo)) // jezeli nie uda sie zaladowac z pliku obrazu
        displayErrorWindow("nie udalo sie zaladowac tla!"); // wyswietla komunikat o niepowodzeniu

    tlo.setTexture(tlo_tekstura); // ustawienie tekstury tla jako sprite
    tlo.setPosition(0,0); // ustawienie pozycji na poczatku ekranu
}
