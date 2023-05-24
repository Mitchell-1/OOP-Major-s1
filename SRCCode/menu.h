#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

class Menu {
    private:
    std::vector<sf::Sprite*> sprites;//position 0 is press enter text
    std::vector<sf::Text*> texts;
    std::string highScore;
    std::string score;
    sf::Clock aniClock;
    bool black = false;
    public:
    Menu(int highScore, sf::Texture *title, sf::Texture *enter, sf::Texture *enemies, sf::Font *font);
    void update(sf::RenderWindow *win, bool &menu, sf::Clock &timer);
    void draw();
    std::string getHighScore() {return this->highScore;}
    void animate();
    ~Menu();
};

#endif