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
    player = new Player(10, 800, 300, texture);
    win = new sf::RenderWindow(sf::VideoMode(x,y),title);
    win->setFramerateLimit(200);
    initLevels();
    levelCreate(level1);
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
            level[i]->update(win, player->getBullets());
            if (level[i]->isDead)
            {
                delete level[i];
                level[i] = nullptr;
            }
        }
    }
    player->update(win);
    }
    player->draw(win);
    
    for(int i = 0; i <30; i++)
    {
        if (level[i] != nullptr)
        {   
            level[i]->animation(gameClock);
            level[i]->draw(win);
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
    
    for (int posX = 50; posX < win->getSize().x; posX+= win->getSize().x/10)
    {
        if (ArrPos == 30)
            break;
        switch (levelArr[ArrPos]) {
            case 0: 
                level[ArrPos] = nullptr;
                break;
            case 1: 
                enemy* en = new enemy(19, 10, posX, posY, this->texture);
                level[ArrPos] = en;
                break;
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
