#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#ifndef GAME_H
#define GAME_H

class game {
    private:
    sf::RenderWindow* win;
    Player *player;
    enemy * en1;
    public:
    game(int x, int y, std::string title);
    void run();
    ~game();

};

#endif