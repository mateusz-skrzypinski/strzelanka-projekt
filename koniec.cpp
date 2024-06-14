#include "include/koniec.h"

Koniec::Koniec(bool arg_wygrana)
{
    wygrana = arg_wygrana;
    if(wygrana)
        tekstura.loadFromFile(wygrano);
    else
        tekstura.loadFromFile(przegrana);


    tlo.setTexture(tekstura);
    tlo.setPosition(0,0);

}

void Koniec::run()
{
    sf::RenderWindow window(sf::VideoMode(1024,1024),"3098 PIXTLE");
    sf::Image icon;
    icon.loadFromFile("../../img/logo.png");

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Font font;
    font.loadFromFile("../../font/Honk-Regular.ttf");
    sf::Text play_button("", font, 70);
    sf::Text message("", font, 70);

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        if (wygrana) {
            play_button.setString("Przejdz do nastepnego poziomu");
            message.setString("Wygrana!");
        }
        else {
            play_button.setString("Zagraj ponownie");
            message.setString("Nie udalo sie, sprobuj ponownie");
        }
        play_button.setOrigin(play_button.getGlobalBounds().width/2,play_button.getGlobalBounds().height/2);
        message.setOrigin(message.getGlobalBounds().width/2, message.getGlobalBounds().height/2);
        play_button.setPosition(window.getSize().x/2, window.getSize().y/2);
        message.setPosition(window.getSize().x/2, window.getSize().y/2 - 300);

        window.draw(tlo);
        window.draw(play_button);
        window.draw(message);
        window.display();
    }
}
