#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#ifndef GAME_H
#define GAME_H

class game {
    private:
    sf::RenderWindow* win;
    Player *player;
    public:
    game(int x, int y, std::string title);
    void run();
    ~game();

};

#endif