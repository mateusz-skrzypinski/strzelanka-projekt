#ifndef SHOPMENU_H
#define SHOPMENU_H

#include "include/menu.h"
#include "include/Guns.h"
#include "include/Character.h"

class ShopMenu : public Menu {
private:
    sf::Text weaponUpgrade, healthUpgrade;
    sf::Text playerStats;
    sf::Text skillSlot1, skillSlot2;
    sf::Text continueButton;
    int playerCoins = 100000; // Początkowa liczba monet gracza
    int& playerHealth;
    int& playerDamage;
    std::string skill1 = "Umiejetnosc X";
    std::string skill2 = "Umiejetnosc Y";

    void initialize(sf::RenderWindow& window);
    void updatePlayerStats();
    void updateSkillsText();

public:
    ShopMenu(sf::RenderWindow& window, Guns& gun, Character& player);
    void run(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window) override;
};

#endif // SHOPMENU_H
