#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "bullet.h"
#include "player.h"
#include "levels/level1.h"

game::game(int x, int y, std::string title) 
{
    player = new Player(10, 100, 300);
    en1 = new enemy(19, 10, 100, 100);
    win = new sf::RenderWindow(sf::VideoMode(x,y),title);
    levelCreate(level1);
}

void game::run() {
    while (win->isOpen()) 
    {

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
        win->clear();
        player->update(win);
        //bullet->update();//this and the line below need to be changed to allow for player to manage bullets
        //bullet->draw(win);
        for (int num = 0; num <30; num ++){
            level[num]->draw(win);
        }
        player->draw(win);
        en1->update();
        win->display();
    }
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
        switch (levelArr[ArrPos]) {
            case 0: break;
            case 1: 
                enemy * en = new enemy(19, 10, posX, posY);
                std::cout << "enemy " << count << " is added" << std::endl;
                level[count] = en;
                count++; 
        }
        ArrPos++;
    }
    
}

};
game::~game(){};