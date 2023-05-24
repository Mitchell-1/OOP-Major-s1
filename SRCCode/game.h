#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include "weak.h"
#include "strong.h"
#include "fast.h"
#include <vector>
#include "bullet.h"
#include <queue> //for levels
#include "powers.h"
#include "levels/levels.h"
#include "livesUi.h"

class game {
    private:
    sf::RenderWindow* win;
    Player* player;
    enemy ** level;
    LivesUi * livesUi;
    float offset = 0;
    float tpf;
    int tickRate = 60;
    sf::Clock dtClock;
    sf::Clock gameClock;
    std::queue<int*[30]> levels;
    std::vector<powerUp*> currentPowerUps;
    int currentLevel = 0;
    float dt;
    sf::Texture* texture;
    int currentEn = 0;
    std::vector<Bullet*> enemyBullets;
    int difficulty = 0;
    int frameCap = 200;
    levelList allLevels;

    public:
    void powerValidity();
    enemy** getLevel() {return level;};
    int getCurrLevel() {return currentLevel;};
    int getTickRate() {return tickRate;};
    int getframeCap() {return frameCap;};
    float getTPF() {return tpf;};
    std::vector<Bullet*>& getBullets(){return this->enemyBullets;};
    game(int x, int y, std::string title);
    void run();
    void levelManager();
    void levelCreate(int (&levelArr)[30]);
    void render();
    void update();
    ~game();
    void updateDt();
    void bulletValidity();
    void gameTest();

};

#endif