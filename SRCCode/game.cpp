#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "bullet.h"
#include "player.h"
#include "state.h"
#include "levels/level1.h"
#include <cmath>

game::game(int x, int y, std::string title) 
{
    player = new Player(10, 100, 300);
    win = new sf::RenderWindow(sf::VideoMode(x,y),title);
    win->setFramerateLimit(200);
    initStates();
    levelCreate(level1);
}

game::~game() 
{
    delete this->win;

    while (!this->states.empty()) 
    {
        delete this->states.top();
        this->states.pop();
    }
}

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
            if (level[i]->isDead){
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
            level[i]->draw(win);
        }
    }
    win->display();
    
}

void game::levelCreate(int (&levelArr)[30])
{
level = new enemy*[30];
unsigned short count;
unsigned int ArrPos = 0;
for (int posY = 50; posY <win->getSize().y-50; posY+= 200) 
{
    
    for (int posX = 50; posX < win->getSize().x; posX+= 300) 
    {
        if (ArrPos == 30)
            break;
        switch (levelArr[ArrPos]) {
            case 0: 
                level[ArrPos] = nullptr;
                break;
            case 1: 
                enemy * en = new enemy(19, 10, posX, posY);
                level[ArrPos] = en;
                
                break;
            
        }
        ArrPos++;
    }
    
}

};

void game::run() {

    while (win->isOpen()) 
    {   
        this->update();
    }
}
