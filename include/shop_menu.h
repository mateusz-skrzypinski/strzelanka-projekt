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
    Skills* skill_slot1a;
    Skills* skill_slot1b;
    Skills* skill_slot2a;
    Skills* skill_slot2b;

    Skills** skill_first_slot;
    Skills** skill_second_slot;

    void initialize(sf::RenderWindow& window);
    void updatePlayerStats();
    void updateSkillsText();

public:
    ShopMenu(sf::RenderWindow& window, Guns& gun, Character& player, Skills* s1a, Skills* s1b, Skills* s2a, Skills* s2b);
    void run(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window) override;
};

#endif // SHOPMENU_H
