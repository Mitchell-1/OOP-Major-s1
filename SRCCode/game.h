
#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include <vector>
#include "bullet.h"
#include <stack> //for gamestates
#include "state.h"
class game {
    private:
    sf::RenderWindow* win;
    Player* player;
    enemy * en1;
    enemy ** level;
    std::stack<State*> states;
    int ptime = 0;
    int offset = 0;
    int tickRate = 120;
    sf::Clock dtClock;
    float dt;
    public:
    game(int x, int y, std::string title);
    void run();
    void levelCreate(int (&levelArr)[30]);
    void render();
    void update();
    ~game();
    int deltaTime(int, int);
    void updateDt();

    void initStates();

};

#endif