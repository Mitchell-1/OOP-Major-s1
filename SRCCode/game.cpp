#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "bullet.h"
#include "player.h"
#include "levels/levels.h"
#include <cmath>

game::game(int x, int y, std::string title) 
{
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/SpriteMap.png");
    player = new Player(800, 800, texture);
    win = new sf::RenderWindow(sf::VideoMode(x,y),title);
    win->setFramerateLimit(200);
    initLevels();
    levelCreate(level9);
    //weakEnemy * weak = new weakEnemy(10, 10, 100, 500, this->texture);
}

game::~game(){};

void game::initStates() 
{
    //this->states.push(new GameState(this->win));
}

void game::updateDt() 
{
    /*Updates the dt variable with the time it takes to update and rende rone frame*/

    this->dt = this->dtClock.restart().asSeconds();
    this->tpf = this->tickRate/(1/this->dt) + offset;
    this->offset = this->tpf-floor(this->tpf);
    this->tpf = floor(this->tpf);
    //std::cout << "Seconds per frame: " << this->dt << ", ticks per frame: " << tpf << ", offset: " << offset << std::endl;
}



void game::render() 
{
    win->clear();
    
    win->display();
}

void game::update() 
{
    if (this->gameClock.getElapsedTime().asSeconds() >= 30000)
        gameClock.restart().asSeconds();
    this->updateDt();
    win->clear();
    
    for (int i = 0; i < this->tpf; i++) 
    {
        //std::cout << i << std::endl;
    sf::Event e;
    
    
    while (win->pollEvent(e)) 
    {
        if (e.type == sf::Event::Closed) 
        {
            win->close();
        }
        if (e.type == sf::Event::KeyPressed)
            {player->processEvents(e.key.code, true);}
        if (e.type == sf::Event::KeyReleased)
            {player->processEvents(e.key.code, false);}
    }

    /*checks hit collision of bullets and enemies*/
    for(int i = 0; i <30; i++)
    {
        if (level[i] != nullptr)
        {
                level[i]->shoot(this->enemyBullets);
                level[i]->update(win, player->getBullets(), enemyBullets);

            
            if (level[i]->isDead)
            {
                
                delete level[i];
                level[i] = nullptr;
            }
        }
    }
    for (int i = 0; i < enemyBullets.size(); i++) 
    {
        enemyBullets.at(i)->update();
    }

    player->update(win);
    }
    player->draw(win);
    
    for(int i = 0; i <30; i++)
    {
        if (level[i] != nullptr)
        {   
            level[i]->animation(gameClock);
            level[i]->draw(win, enemyBullets);
        }
    }
    if (gameClock.getElapsedTime().asSeconds() >= 1)
        gameClock.restart();
    win->display();
    
}

void game::levelCreate(int (&levelArr)[30])
{

level = new enemy*[30];
unsigned short count;
unsigned int ArrPos = 0;
for (int posY = 50; posY <win->getSize().y-50; posY+= 200) 
{
    
    for (int posX = 10; posX < win->getSize().x; posX+= win->getSize().x/10)
    {
        if (ArrPos == 30)
            break;
        switch (levelArr[ArrPos]) {
            case 0: 
            {
                level[ArrPos] = nullptr;
                break;
            }
            case 1: 
            {
                weakEnemy* Wen = new weakEnemy(posX, posY, this->texture);
                level[ArrPos] = Wen;
                break;
            }
            case 2:
            {
                strongEnemy* Sen = new strongEnemy(posX, posY, this->texture);
                level[ArrPos] = Sen;
                break;
            }
            case 3:
            {
                fastEnemy* Fen = new fastEnemy(posX, posY, this->texture);
                level[ArrPos] = Fen;
                break;
            }
        }
        ArrPos++;
    }
    
}

};

void game::initLevels() {
    /*
    for (int i = 0; i <9; i++) 
    {
        int* levelTemp = *levelList[i];
        levels.push(levelTemp);
    }
    levelCreate(levels.front());*/
}

void game::levelManager() 
{   

}

void game::run() {

    while (win->isOpen()) 
    {   
        this->update();
    }
}
