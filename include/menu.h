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
    sf::Texture tlo_tekstura;
    sf::Sprite tlo;

    std::string s_tlo = "../../img/tlo.png";

    void displayErrorWindow(const std::string& errorMsg);

    void animacja(sf::Text& t, sf::RenderWindow& window);

    bool kontynuj = true;
    void zaladuj_tlo();
public:
    virtual ~Menu() = default;
    virtual void run(sf::RenderWindow& window) = 0;
    virtual void handleEvents(sf::RenderWindow& window) = 0;
};

#endif // MENU_H
