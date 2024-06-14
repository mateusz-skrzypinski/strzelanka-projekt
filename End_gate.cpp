#include "include/End_gate.h"

End_gate::End_gate() {
    end_gate_texture.loadFromFile("../../img/End_gate.png");
    this->setTexture(end_gate_texture);
    this->setScale(2,2);
    this->setPosition(1750,500); // pozycja koncowa
    time = 1.5; // czas przez ktory gracz musi stac we fladze, zeby przejsc poziom
    timer = 0; // czas ile tam juz stoi
}

bool End_gate::check_collision(sf::FloatRect object_rect) { // sprawdzenie kolizji flagi i obiektu
    return this->getGlobalBounds().intersects(object_rect);
}
