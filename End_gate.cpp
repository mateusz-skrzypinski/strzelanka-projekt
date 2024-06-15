#include "include/End_gate.h"

End_gate::End_gate() {
    end_gate_texture.loadFromFile("../../img/End_gate.png"); // pobieranie tekstury
    this->setTexture(end_gate_texture); // ustawienie tekstury baneru końcowego
    this->setScale(2,2); // ustawienie skali tekstury, żeby miałą porządany rozmiar
    this->setPosition(1750,500); // pozycja koncowa - ta do której musi dojść bohater
    time = 1.5; // czas przez ktory gracz musi stac we fladze, zeby przejsc poziom
    timer = 0; // czas ile tam juz stoi
}

bool End_gate::check_collision(sf::FloatRect object_rect) { // sprawdzenie kolizji flagi i obiektu
    return this->getGlobalBounds().intersects(object_rect);
}
