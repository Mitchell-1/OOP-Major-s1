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
#include <stack> //for gamestates
#include <queue> //for levels
#include "powers.h"
class game {
    private:
    sf::RenderWindow* win;
    Player* player;
    enemy ** level;
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

    public:
    std::vector<Bullet*>& getBullets(){return this->enemyBullets;};
    game(int x, int y, std::string title);
    void run();
    void initLevels();
    void levelManager();
    void levelCreate(int (&levelArr)[30]);
    void render();
    void update();
    float deltaTime (float, float);
    ~game();
    void updateDt();
    void bulletValidity();
    void livesRender();

};

#endif