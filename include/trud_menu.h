#ifndef TRUDMENU_H
#define TRUDMENU_H

#include "include/menu.h"

class DifficultyMenu : public Menu {
private:
    sf::Text easy, medium, hard;
    void initialize(sf::RenderWindow& window);



public:
    DifficultyMenu(sf::RenderWindow& window);
    void run(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window) override;
    static double mnoznik_trud;
};

#endif // TRUDMENU_H
