#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>

game::game(int x, int y, std::string title) 
{
    player = new Player(10, 100, 100);
    win = new sf::RenderWindow(sf::VideoMode(x,y),title);
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
        player->draw(win);
        player->update();
        win->display();
    }
}
game::~game(){};