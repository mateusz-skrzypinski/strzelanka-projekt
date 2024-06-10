#ifndef STARTMENU_H
#define STARTMENU_H

#include "menu.h"

class StartMenu : public Menu {
private:
    sf::Texture t_logo;
    sf::Sprite logo;
    const std::string s_logo = "../../img/logo.png";

    sf::Text start, trud, pomoc;

    void help();
    void initialize(sf::RenderWindow& window);

public:
    StartMenu(sf::RenderWindow& window);
    void run(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window) override;
};

#endif // STARTMENU_H
