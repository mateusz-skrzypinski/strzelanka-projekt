#ifndef KONIEC_H
#define KONIEC_H

#include "include/menu.h"

class Koniec
{
private:
    sf::Texture tekstura;
    std::string wygrano = "../../img/wygrana.png";
    std::string przegrana = "../../img/przegrana.png";
    sf::Sprite tlo;
    bool wygrana;
public:
    Koniec(bool arg_wygrana);
    void run();
};

#endif // KONIEC_H
