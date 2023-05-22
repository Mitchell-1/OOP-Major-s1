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
    levelManager();
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
    if (currentEn == 0)
    {
        currentLevel++;
        levelManager();
    }
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
                level[i]->update(win, player->getBullets());

            
            if (level[i]->isDead)
            {
                currentEn --;
                //std::cout << currentEn << std::endl;
                delete level[i];
                level[i] = nullptr;
            }
        }
    }
    for (int i = 0; i < enemyBullets.size(); i++) 
    {
        enemyBullets.at(i)->update();
    }

    bulletValidity();
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

    for (int i = 0; i <enemyBullets.size(); i++)
    {
        enemyBullets.at(i)->draw(win);
    }

    if (gameClock.getElapsedTime().asSeconds() >= 1)
        gameClock.restart();
    win->display();
    
}

void game::levelCreate(int (&levelArr)[30])
{

level = new enemy*[30];
delete level;
level = new enemy*[30];
unsigned short count;
unsigned int ArrPos = 0;
for (int posY = 50; posY <win->getSize().y; posY+= 200) 
{
    
    for (int posX = 50; posX < win->getSize().x; posX+= win->getSize().x/10)
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
                weakEnemy* Wen = new weakEnemy(posX, posY, this->texture, this->difficulty);
                level[ArrPos] = Wen;
                break;
            }
            case 2:
            {
                strongEnemy* Sen = new strongEnemy(posX, posY, this->texture, this->difficulty);
                level[ArrPos] = Sen;
                break;
            }
            case 3:
            {
                fastEnemy* Fen = new fastEnemy(posX, posY, this->texture, this->difficulty);
                level[ArrPos] = Fen;
                break;
            }
        }
        ArrPos++;
    }
    
}

};

void game::bulletValidity() 
{
    if (!this->enemyBullets.empty()) 
    {
            if(this->enemyBullets.at(0)->checkOutOfBounds(win)) /*only check first one, as it will always be the highest*/
            {
                /*remove bullet object and call destructor to free up memory*/

                delete this->enemyBullets.at(0);

                /*delete pointer from vector*/
                this->enemyBullets.erase(enemyBullets.begin());
            }           
    }
}

void game::levelManager() 
{   
    switch (currentLevel)
    {
    case 2:
    {
        levelCreate(level2);
        currentEn = level2Size;
        break;
    }
    case 3:
    {
        levelCreate(level3);
        currentEn = level3Size;
        break;
    }
    case 4:
    {
        levelCreate(level4);
        currentEn = level4Size;
        break;
    }
    case 5:
    {
        levelCreate(level5);
        currentEn = level5Size;
        break;
    }
    case 6:
    {
        levelCreate(level6);
        currentEn = level6Size;
        break;
    }
    case 7:
    {
        levelCreate(level7);
        currentEn = level7Size;
        break;
    }
    case 8:
    {
        levelCreate(level8);
        currentEn = level8Size;
        break;
    }
    case 9:
    {
        levelCreate(level9);
        currentEn = level9Size;
        break;
    }
    default:
    {
        currentLevel = 1;
        difficulty ++;
        levelCreate(level1);
        currentEn = level1Size;
        break;
    }
    }
}

void game::run() {

    while (win->isOpen()) 
    {   
        this->update();
    }
}
