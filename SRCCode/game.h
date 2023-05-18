
#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include <vector>
#include "bullet.h"
class game {
    private:
    sf::RenderWindow* win;
    Player* player;
    enemy * en1;
    enemy ** level;
    public:
    game(int x, int y, std::string title);
    void run();
    void levelCreate(int (&levelArr)[30]);
    ~game();

};

#endif