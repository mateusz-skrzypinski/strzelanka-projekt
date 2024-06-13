#include "include/shop_menu.h"

ShopMenu::ShopMenu(sf::RenderWindow& window, Guns& gun, Character& player, Skills* s1a, Skills* s1b, Skills* s2a, Skills* s2b)
    :playerHealth(player.hp), playerDamage(gun.damage), skill_slot1a(s1a), skill_slot1b(s1b),
    skill_slot2a(s2a), skill_slot2b(s2b), skill_first_slot(&player.skill_first_slot), skill_second_slot(&player.skill_second_slot)
{
    initialize(window);
}

void ShopMenu::initialize(sf::RenderWindow& window) {
    if (!font.loadFromFile("../../font/Honk-Regular.ttf")) {
        displayErrorWindow("Nie mozna zaladowac czcionki");
        return;
    }

    weaponUpgrade.setFont(font);
    weaponUpgrade.setString("Ulepsz bron (50 monet)");
    weaponUpgrade.setCharacterSize(70);
    weaponUpgrade.setFillColor(nieaktywny);
    weaponUpgrade.setPosition(50, 20);

    healthUpgrade.setFont(font);
    healthUpgrade.setString("Zwieksz poziom zycia (30 monet)");
    healthUpgrade.setCharacterSize(70);
    healthUpgrade.setFillColor(nieaktywny);
    healthUpgrade.setPosition(50, 140);

    playerStats.setFont(font);
    playerStats.setCharacterSize(40);
    playerStats.setFillColor(sf::Color::White);
    updatePlayerStats();
    playerStats.setOrigin(playerStats.getLocalBounds().width, 0);
    playerStats.setPosition(window.getSize().x - 50, 20);

    skillSlot1.setFont(font);
    skillSlot1.setCharacterSize(50);
    skillSlot1.setFillColor(nieaktywny);
    skillSlot1.setPosition(50, window.getSize().y - 300);

    skillSlot2.setFont(font);
    skillSlot2.setCharacterSize(50);
    skillSlot2.setFillColor(nieaktywny);
    skillSlot2.setPosition(50, window.getSize().y - 180);
    updateSkillsText();

    continueButton.setFont(font);
    continueButton.setString("Kontynuuj");
    continueButton.setCharacterSize(80);
    continueButton.setFillColor(nieaktywny);
    continueButton.setOrigin(continueButton.getLocalBounds().width, continueButton.getLocalBounds().height);
    continueButton.setPosition(window.getSize().x - 50, window.getSize().y - 150);
}

void ShopMenu::updatePlayerStats() {
    playerStats.setString("Poziom zycia: " + std::to_string(playerHealth) + "\nObrazenia: " + std::to_string(playerDamage) + "\nKredyty: " + std::to_string(playerCoins) + "cr");
}

void ShopMenu::updateSkillsText() {
    skillSlot1.setString("Zmien umiejetnosc: " + skill_slot1a->name);
    skillSlot2.setString("Zmien umiejetnosc: " + skill_slot2a->name);
}

void ShopMenu::run(sf::RenderWindow& window) {
    while (window.isOpen() && kontynuj) {
        handleEvents(window);

        window.clear(sf::Color::Black);
        window.draw(weaponUpgrade);
        window.draw(healthUpgrade);
        window.draw(playerStats);
        window.draw(skillSlot1);
        window.draw(skillSlot2);
        window.draw(continueButton);
        window.display();
    }
}

void ShopMenu::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (weaponUpgrade.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (playerCoins >= 50) {
                        playerDamage += 1; // Ulepsz broń
                        playerCoins -= 50; // Odejmij koszt ulepszenia
                        updatePlayerStats();
                    }
                    return;
                }

                if (healthUpgrade.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (playerCoins >= 30) {
                        playerHealth += 20; // Zwiększ poziom życia
                        playerCoins -= 30; // Odejmij koszt ulepszenia
                        updatePlayerStats();
                    }
                    return;
                }

                if (skillSlot1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (skillSlot1.getString() == sf::String("Zmien umiejetnosc: ") + skill_slot1a->name) {
                        skillSlot1.setString("Zmien umiejetnosc: " + skill_slot1b->name);
                        *skill_first_slot = skill_slot1a;
                    } else {
                        skillSlot1.setString("Zmien umiejetnosc: " + skill_slot1a->name);
                        *skill_first_slot = skill_slot1b;
                    }
                    return;
                }

                if (skillSlot2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (skillSlot2.getString() == sf::String("Zmien umiejetnosc: ") + skill_slot2a->name) {
                        skillSlot2.setString("Zmien umiejetnosc: " + skill_slot2b->name);
                        *skill_second_slot = skill_slot2a;
                    } else {
                        skillSlot2.setString("Zmien umiejetnosc: " + skill_slot2a->name);
                        *skill_second_slot = skill_slot2b;
                    }
                    return;
                }

                if (continueButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    kontynuj = false;
                    return;
                }
            }
        }
    }

    animacja(weaponUpgrade, window);
    animacja(healthUpgrade, window);
    animacja(skillSlot1, window);
    animacja(skillSlot2, window);
    animacja(continueButton, window);
}
