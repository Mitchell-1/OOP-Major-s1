#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>

game::game(int x, int y, std::string title) 
{
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
        }
        win->clear();
        win->display();
    }
}
game::~game(){};