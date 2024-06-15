#include "include/shop_menu.h"

// konstruktor pobiera wartosci:
// okna po referencji - zeby mogl na nim wyswietlac
// klasy Gun, broni po referencji - zeby mogl w latwy sposob zmieniac jego atrybuty
// gracza poprzez refenrecje - zeby dostac sie do jego zdrowia i ustawionych na pierwszym i drugim slocie umiejetnosci
// zainicjalizowanie w "main.cpp" wartosci 4 roznych spelli - slot 1a, slot 1b, slot 2a, slot 2b sa one zapisane skrotowo
ShopMenu::ShopMenu(sf::RenderWindow& window, Guns& gun, Character& player, Skills* s1a, Skills* s1b, Skills* s2a, Skills* s2b)
    :playerHealth(player.hp), playerDamage(gun.damage), skill_slot1a(s1a), skill_slot1b(s1b),
    skill_slot2a(s2a), skill_slot2b(s2b), skill_first_slot(&player.skill_first_slot), skill_second_slot(&player.skill_second_slot)
{
    initialize(window); // uruchamia metode, ktora definiuje przyciski w formie tekstu
    *skill_first_slot = skill_slot1b;  // przypisuje wartosci domyslne dla podwojnego wskaznika,
    *skill_second_slot = skill_slot2b; // zeby przypisac wartosci do player.skill_fist_slot i player.skill_second_slot
}

void ShopMenu::initialize(sf::RenderWindow& window) { // pobiera argument window, zeby odczytac jego szerokosc i wysokosc
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) { // proba zaladowania czcionki
        displayErrorWindow("Nie mozna zaladowac czcionki"); // inicjalzacja okna niepowodzenia zdefiniowana w "menu.cpp" z komunikatem
        return;                                             // "Nie mozna zaladowac czcionki" i wychodzi z metody
    }
    zaladuj_tlo(); // wywoluje metode zdefiniowana w "menu.cpp" do ladowania tla

    // definicja przycisku "weaponUpgrade" do ulepszania atrybutow broni - jej obrazen
    weaponUpgrade.setFont(font);  // przypisanie jej czcionki
    weaponUpgrade.setString("Ulepsz bron (50 monet)"); // przypisanie jej wartosci string - wiadomosci ktora wyswietla
    weaponUpgrade.setCharacterSize(70); // przypisanie wielkosci czcionki
    weaponUpgrade.setFillColor(nieaktywny); // przypisanie domyslnego koloru jako nieaktywnego, zdefiniowanego bezposrednio w klasie Menu w "menu.h"
    weaponUpgrade.setPosition(50, 20); // ustawienie pozycji przycisku do ulepszania broni

    // definicja przycisku "healthUpgrade" do ulepszenie maksymalnego zdrowia bohatera poprzez referencje - wartosc "int &playerHealth& zadeklarowana w "shop_menu.h"
    healthUpgrade.setFont(font); // przypisanie jej czcionki                                                  i przypisanie jej wartosci w konstruktorze w tym pliku
    healthUpgrade.setString("Zwieksz poziom zycia (30 monet)"); // przypisanie jej wartosci string - wiadomosci ktora wyswietla
    healthUpgrade.setCharacterSize(70); // przypisanie wielkosci czcionki
    healthUpgrade.setFillColor(nieaktywny); // przypisanie domyslnego koloru jako nieaktywnego, zdefiniowanego bezposrednio w klasie Menu w "menu.h"
    healthUpgrade.setPosition(50, 140); // ustawienie pozycji przycisku do ulepszania broni

    // definicja "playerStats" do wyswitlania informacji o aktualnych statystykach - jego zdrowiu, obrazeniach i kredytach
    playerStats.setFont(font); // przypisanie jej czcionki
    playerStats.setCharacterSize(40); // przypisanie jej wielkosci czcionki
    playerStats.setFillColor(sf::Color::White); // przypisanie jej stalego koloru, gdyz nie jest to przypisk, wiec nie zmienia swojego koloru po najechaniu
    updatePlayerStats(); // uaktualnia wartosci statystyk bohatera na podstawie zmiennych zdeklarowanych w "shop_menu.h" i zdefiniowanych w konstruktorze tego pliku
    playerStats.setOrigin(playerStats.getLocalBounds().width, 0); // ustawienie jej innego punktu odniesienia
    playerStats.setPosition(window.getSize().x - 50, 20); // ustawienie jej wartosci wzgledem pozycji okna

    // definicja przycisku "skillSlot1" dla zmiany umiejetnosci dla pierwszego slota bohatera - dash/teleport
    skillSlot1.setFont(font); // przypisanie jej czcionki
    skillSlot1.setCharacterSize(50); // przypisanie jej wielkosci czcionki
    skillSlot1.setFillColor(nieaktywny); // ustawienie jej domyslnego koloru zdefiniowanego bezposrednio w klasie bazowej "menu.h"
    skillSlot1.setPosition(50, window.getSize().y - 300); // ustawienie jej pozycji na oknie

    // definicja przycisku "skillSlot2" dla zmiany umiejetnosci dla drugiego slota bohatera - fireball/zap
    skillSlot2.setFont(font); // przypisanie jej czcionki
    skillSlot2.setCharacterSize(50); // przypisanie jej wielkosci czcionki
    skillSlot2.setFillColor(nieaktywny); // ustawienie jej domyslnego koloru zdefiniowanego bezposrednio w klasie bazowej "menu.h"
    skillSlot2.setPosition(50, window.getSize().y - 180); // ustawienie jej pozycji na okie
    updateSkillsText(); // aktualizacja wyswietlanego tekstu w zaleznosci jaka umiejetnosc zostala przypisana

    // definicja przycisku "continueButton", ktory jest odpowiedzialny za wyjscie ze sklepu i wejscie do poziomu
    continueButton.setFont(font); // ustawienie jej czcionki
    continueButton.setString("Kontynuuj"); // ustawienie jej wartosci wyswietlanej - "Kontynuuj
    continueButton.setCharacterSize(80); // ustawienie jej wielkosci czcionki
    continueButton.setFillColor(nieaktywny); // ustawienie jej doyslnego koloru zdefiniowanego bezposrednio w klasie bazowej "menu.h"
    continueButton.setOrigin(continueButton.getLocalBounds().width, continueButton.getLocalBounds().height); // ustawienie innego punktu odniesienia
    continueButton.setPosition(window.getSize().x - 50, window.getSize().y - 150); // ustawienie przycisku na oknie wzgledem wielkosci okna
}

void ShopMenu::updatePlayerStats() { // uaktualnia wartosci statystyk bohatera na podstawie zmiennych zdeklarowanych w "shop_menu.h" i zdefiniowanych w konstruktorze tego pliku
    playerStats.setString("Poziom zycia: " + std::to_string(playerHealth) + "\nObrazenia: " + std::to_string(playerDamage) + "\nKredyty: " + std::to_string(playerCoins) + "cr");
    // jest to laczony string skladajacy sie z wyswietlenia poziomu zycia, w nastepnej lini ilosci zadawanych obrazen przy jednym strzale, w nastepnej lini ilosci kredytow
}

void ShopMenu::updateSkillsText() { // aktualizacja wyswietlanego tekstu w zaleznosci jaka umiejetnosc zostala przypisana
    skillSlot1.setString("Zmien umiejetnosc: " + skill_slot1a->name); // aktualizacja przycisku zmiany 1
    skillSlot2.setString("Zmien umiejetnosc: " + skill_slot2a->name); // aktualizacja przycisku zmiany 2
}

void ShopMenu::run(sf::RenderWindow& window) { // metoda wyswietlajaca na oknie przyciski zdefiniowane w metodzie "initialize"
    while (window.isOpen() && kontynuj) { // petla programu dopoki okno jest otwarte i flaga kontynuuj ma wartosc true, kontynuuj ma domyslna wartosc true
        handleEvents(window); // cala implementacja do zarzadzania przyciskami jest opisana w metodzie handleEvents

        // renderowanie
        window.clear(sf::Color::Black); // czyszczenie okna
        window.draw(tlo); // rysowanie tla
        window.draw(weaponUpgrade); // rysowanie przyciskow
        window.draw(healthUpgrade); // rysowanie przyciskow
        window.draw(playerStats); // rysowanie przyciskow
        window.draw(skillSlot1); // rysowanie przyciskow
        window.draw(skillSlot2); // rysowanie przyciskow
        window.draw(continueButton); // rysowanie przyciskow
        window.display(); // wyswietlanie
    }
}

void ShopMenu::handleEvents(sf::RenderWindow& window) { // cala implementacja do zarzadzania przyciskami jest opisana w metodzie handleEvents
    sf::Event event; // zdeklarowanie zmiennej Event
    while (window.pollEvent(event)) { // jesli window zarejestruje jakies zdarzenie, to:
        if (event.type == sf::Event::Closed) { // 1. jesli gracz chce zamknac okno, to
            window.close(); // zamyka okno
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pobieranie pozycji myszki z okna do sprawdzenia jej pozycji
        if (event.type == sf::Event::MouseButtonPressed) { // 2. jesli gracz nacisnie na lewy przycisk myszy, to sprawdza, czy nie zostal klikniety w jakis przycisk
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (weaponUpgrade.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacisnieto przycisk do ulepszenia broni
                    if (playerCoins >= 50) { // sprawdzenie, czy gracz ma wystarczajaco kredytow
                        playerDamage += 1; // Ulepsz broń
                        playerCoins -= 50; // Odejmij koszt ulepszenia
                        updatePlayerStats(); // aktualizacja jego statystyk, definicja metody powyzej
                    }
                    return; // wychodzi z handleEvents
                }

                if (healthUpgrade.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacisnieto przycisk do ulepszenia zdrowia bohatera
                    if (playerCoins >= 30) { // sprawdzenie, czy gracz ma wystarczajaco kredytow
                        playerHealth += 20; // Zwiększ poziom życia
                        playerCoins -= 30; // Odejmij koszt ulepszenia
                        updatePlayerStats(); // aktualizacja jego statystyk, definicja metody powyzej
                    }
                    return; // wychodzi z handleEvents
                }

                if (skillSlot1.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacisnieto przycisk do zmiany pierwszej umiejetnosci
                    if (skillSlot1.getString() == sf::String("Zmien umiejetnosc: ") + skill_slot1a->name) { // sprawdzenie ktora umiejetnosc jest przypisana poprzez sprawdzenie jej nazwy
                        skillSlot1.setString("Zmien umiejetnosc: " + skill_slot1b->name); // ustawienie drugiej umiejetnosci niz ta co jest ustawiona i zmienienie jej wyswietlanego tekstu
                        *skill_first_slot = skill_slot1a;
                    } else { // jesli nazwa sie nie zgadza, to zmienia na pierwsza umiejetnosc
                        skillSlot1.setString("Zmien umiejetnosc: " + skill_slot1a->name); // ustawienie drugiej umiejetnosci niz ta co jest ustawiona i zmienienie jej wyswietlanego tekstu
                        *skill_first_slot = skill_slot1b;
                    }
                    return;
                }

                if (skillSlot2.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacisnieto przycisk do zmiany drugiej umiejetnosci
                    if (skillSlot2.getString() == sf::String("Zmien umiejetnosc: ") + skill_slot2a->name) { // sprawdzenie ktora umiejetnosc jest przypisana poprzez sprawdzenie jej nazwy
                        skillSlot2.setString("Zmien umiejetnosc: " + skill_slot2b->name); // ustawienie drugiej umiejetnosci niz ta co jest ustawiona i zmienienie jej wyswietlanego tekstu
                        *skill_second_slot = skill_slot2a;
                    } else { // jesli nazwa sie nie zgadza, to zmienia na pierwsza umiejetnosc
                        skillSlot2.setString("Zmien umiejetnosc: " + skill_slot2a->name); // ustawienie drugiej umiejetnosci niz ta co jest ustawiona i zmienienie jej wyswietlanego tekstu
                        *skill_second_slot = skill_slot2b;
                    }
                    return;
                }

                if (continueButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) { // nacisnieto przycisk do zamkniecia sklepu i rozpoczecia poziomu
                    kontynuj = false;
                    return;
                }
            }
        }
    }

    // wywolanie dla wszystkich przyciskow metody klasy bazowej dla animacji zmiany koloru, jesli myszka najedzie na przycisk , definicja w "menu.h"
    animacja(weaponUpgrade, window);
    animacja(healthUpgrade, window);
    animacja(skillSlot1, window);
    animacja(skillSlot2, window);
    animacja(continueButton, window);
}
