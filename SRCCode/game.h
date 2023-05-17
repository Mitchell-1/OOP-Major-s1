#include <string>
#include <SFML/Graphics.hpp>
#ifndef GAME_H
#define GAME_H

class game {
    private:
    sf::RenderWindow* win;
    public:
    game(int x, int y, std::string title);
    void run();
    ~game();

};

#endif