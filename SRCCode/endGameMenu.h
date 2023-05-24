#ifndef ENDGAMEMENU_H
#define ENDGAMEMENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class endGameMenu {
    private:
    std::vector<sf::Sprite*> sprites;
    int highScore;
    int currentScore;
    public:
    Menu(int highScore, sf::Texture *gameOver);
    void update();
    void draw();
};

#endif