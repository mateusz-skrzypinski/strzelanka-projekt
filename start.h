#ifndef START_H
#define START_H

#include <SFML/Graphics.hpp>

class Start {
private:
    sf::Font font;
    sf::Texture t_logo, t_start, t_trud, t_pomoc;
    sf::Sprite logo, start, trud, pomoc;

    const std::string s_logo = "../../img/logo.png";
    const std::string s_start = "../../img/start.png";
    const std::string s_trud = "../../img/trud.png";
    const std::string s_pomoc = "../../img/pomoc.png";

    void displayErrorWindow(const std::string& errorMsg);
    void help();

public:
    Start();

    void run(sf::RenderWindow& window);
};
#endif // START_H
