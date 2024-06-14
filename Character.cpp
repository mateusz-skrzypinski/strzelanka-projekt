#include "include/Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/trud_menu.h"
#include <cmath>

Character::Character() {
    is_walking = false;
    is_shooting = false;
    skill_first_slot = nullptr;
    skill_second_slot = nullptr;
    load_texture(); // automatyczne ladowanie tekstur do zmiennych
    player_sprite.setOrigin(102,90);
    hit_box.setSize(sf::Vector2f(80, 75)); // wprowadzenie hitboxa, gdyż tekstury chodzenia i strzelania sa inne
    hit_box.setOrigin(40, 40);
    hit_box.setPosition(128,540);
    hp = 100;
    top = 0;
    right = 0;
    initial_speed = 400.0f/DifficultyMenu::mnoznik_trud; //gracz jest wolniejszy jesli ma wyzszy poziom trudnosci
}

Character::~Character() {
    delete skill_first_slot;
    if (skill_second_slot) { // drugi skill nie musi istnieć
        delete skill_second_slot;
    }
}

void Character::move(sf::Vector2f xy_distance) {
    if (slow_timer > 0)
        xy_distance *= slow_factor;
    player_sprite.move(xy_distance);
    hit_box.move(xy_distance);
    // sprawdzenie w ktora strone idzie bohater i odpowiedni obrot
    if (top == 0 && right == 1)
        player_sprite.setRotation(0);
    if (top == -1 && right == 1)
        player_sprite.setRotation(-45.0f);
    if (top == -1 && right == 0)
        player_sprite.setRotation(-90.0f);
    if (top == -1 && right == -1)
        player_sprite.setRotation(-135.0f);
    if (top == 0 && right == -1)
        player_sprite.setRotation(-180.0f);
    if (top == 1 && right == -1)
        player_sprite.setRotation(-225.0f);
    if (top == 1 && right == 0)
        player_sprite.setRotation(-270.0f);
    if (top == 1 && right == 1)
        player_sprite.setRotation(-315.0f);
    top = 0; // zmienne potrzebne zdefiniwac jak porusza sie bohater, zmiana nastepuje w main
    right = 0;
}

sf::Vector2f Character::getPosition() { // funkcja pozwalajaca odwolywac sie do pozycji player_sprite
    return player_sprite.getPosition();
}

void Character::setPosition(sf::Vector2f position) { // funkcja pozwalajaca ustawic pozyce player_sprite
    player_sprite.setPosition(position);
}

void Character::draw(sf::RenderWindow& window, float dt, sf::Vector2f mouse_xy) { // animacja
    slow_timer -= dt; // licznik ile jeszcze bedzie trwac slow
    if (!is_walking && !is_shooting) {  // gracz sie nie porusza
        speed = initial_speed;
        player_sprite.setTexture(peace_texture); // tekstura, gdy stoi w miejscy - nie ma animacji
        window.draw(player_sprite); // rysowanie
        return; // wychodzi z funkcji draw
    }

    // obliczanie aktualnej klatki animacji
    last_frame_time += dt;
    if (last_frame_time > 0.05f) {
        last_frame_time = 0;
        frame_number++;
    }
    if (frame_number > 20) {
        frame_number = 0;
    }

    // jezeli gracz strzela, to przypisuje mu teksture z wektora z animacja strzelania
    if (is_shooting) { // STRZELA
        speed = initial_speed/2; // mniejsza predkosc przy strzelaniu
        if (frame_number < static_cast<int>(shooting_texture.size())) {
            player_sprite.setTexture(shooting_texture[frame_number]);
        } else {
            std::cout << "Error: frame_number (" << frame_number << ") out of range for shooting_texture" << std::endl;
        }

        float alpha; // kat obrotu podazajacym za myszka
        sf::Vector2f dir_vector = mouse_xy - getPosition();
        float norm = std::sqrt(dir_vector.x * dir_vector.x + dir_vector.y * dir_vector.y);
        if (norm != 0) {
            dir_vector = dir_vector / norm;
        }

        if (dir_vector.x > 0) {
            alpha = atan(dir_vector.y / dir_vector.x) * 180/M_PI;

        } else {
            alpha = (M_PI + atan(dir_vector.y / dir_vector.x)) * 180/M_PI;
        }
        player_sprite.setRotation(alpha); // nadanie obrotu, zeby podazal za myszka
    } else { // TYLKO CHODZI
        speed = initial_speed; // przywraca predkosc
        if (frame_number < static_cast<int>(walking_texture.size())) {
            player_sprite.setTexture(walking_texture[frame_number]);
        } else {
            std::cout << "Error: frame_number (" << frame_number << ") out of range for walking_texture" << std::endl;
        }
    }
    window.draw(player_sprite);
    is_walking = false; // zmienne ustawiane sa automatycznie na false i zmieniane w main, jesli
    is_shooting = false; // gracz bedzie strzelac lub chodzic
}


void Character::load_texture() { // automatyczne ladowanie tekstur do zmiennych
    peace_texture.loadFromFile("../../img/walk/6.png");
    for (int i = 1; i <= 21; i++) { // tekstury sa ponumerowane od 1 do 21
        std::string shooting_file_name = "../../img/attack/"; // sciezka dla strzelania
        std::string walking_file_name = "../../img/walk/"; // sciezka dla chodzenia
        sf::Texture walking;
        if (!walking.loadFromFile(walking_file_name + std::to_string(i) + ".png"))
            std::cout << "nie udalo sie zaladowac tekstur" << std::endl;
        walking_texture.emplace_back(walking); // przypisanie do wektora tekstury
        sf::Texture shooting;
        if (!shooting.loadFromFile(shooting_file_name + std::to_string(i) + ".png"))
            std::cout << "nie udalo sie zaladowac tekstury" << std::endl;
        shooting_texture.emplace_back(shooting); // przypisanie do wektora tekstury
    }
}
