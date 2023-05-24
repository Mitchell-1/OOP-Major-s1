#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Menu {
    private:
    std::vector<sf::Sprite*> sprites;//position 0 is press enter text
    int highScore;
    public:
    Menu(int highScore, sf::Texture *title, sf::Texture *enter, sf::Texture *enemies);
    void update(sf::RenderWindow *win, bool &menu, sf::Clock &timer);
    void draw();
};

#endif