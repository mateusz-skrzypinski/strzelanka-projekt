#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
protected:
    sf::Font font;
    sf::Color aktywny = sf::Color::Magenta;
    sf::Color nieaktywny = sf::Color::Cyan;
    std::vector<sf::Text> menuItems;

    void displayErrorWindow(const std::string& errorMsg);

    void animacja(sf::Text& t, sf::RenderWindow& window);

    bool kontynuj = true;
public:
    virtual ~Menu() = default;
    virtual void run(sf::RenderWindow& window) = 0;
    virtual void handleEvents(sf::RenderWindow& window) = 0;
};

#endif // MENU_H
