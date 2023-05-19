#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "bullet.h"
#include "player.h"
#include "state.h"
#include "levels/level1.h"

game::game(int x, int y, std::string title) 
{
    player = new Player(10, 100, 300);
    en1 = new enemy(19, 10, 100, 100);
    win = new sf::RenderWindow(sf::VideoMode(x,y),title);
    win->setFramerateLimit(60);
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

int game::deltaTime(int prev, int offset){
int t = (clock() - prev);
return t;
};

void game::updateDt() 
{
    /*Updates the dt variable with the time it takes to update and rende rone frame*/

    this->dt = this->dtClock.restart().asSeconds();

    //std::cout << this->dt << std::endl;
}



void game::render() 
{
    win->clear();
    
    win->display();
}

void game::update() 
{
    this->updateDt();

    int delta = deltaTime(ptime, offset)+offset;
    ptime = clock();
    sf::Event e;
    win->clear();
    for (int i = 0; i < delta / (1000/tickRate); i++) 
    {

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



    for(int i = 0; i <30; i++)
    {
        if (level[i] != nullptr)
        {
            level[i]->update();
        }
    }

    player->update(win);
    en1->update();

}

    player->draw(win);
    for(int i = 0; i <30; i++)
    {
        if (level[i] != nullptr)
        {
            level[i]->draw(win);
        }
    }
    
    en1->draw(win);
    win->display();
    
    offset = delta % tickRate;
}

void game::levelCreate(int (&levelArr)[30])
{
std::cout << "levelCreate" << std::endl;
level = new enemy*[30];
unsigned short count;
unsigned int ArrPos = 0;
for (int posY = 50; posY <win->getSize().y-50; posY+= 20) 
{
    for (int posX = 50; posX < win->getSize().x; posX+= 30) 
    {
        if (ArrPos == 30)
            break;
        switch (levelArr[ArrPos]) {
            case 0: 
                std::cout << "blank space at " << ArrPos << std::endl;
                level[ArrPos] = nullptr;
                break;
            case 1: 
                enemy * en = new enemy(19, 10, posX, posY);
                std::cout << "enemy " << ArrPos << " is added" << std::endl;
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
