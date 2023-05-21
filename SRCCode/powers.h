#ifndef POWERS_H
#define POWERS_H
#include <SFML/Graphics.hpp>
#include <iostream>

class powerUp {
    private:
        sf::Sprite* body;
        sf::Texture* texture;
        bool isConsumed;
        sf::Clock duration;
        char name;
        int time;
        float speed = 5;

    public:
        unsigned short health = 0;
        unsigned short damage = 0;
        unsigned short reload = 0;
        unsigned short lives = 0;
        powerUp();
        powerUp(char classType, sf::FloatRect enemyPos);
        void draw(sf::RenderWindow *win);
        void update();
        bool checkOutOfBounds(sf::RenderWindow *win);
        ~powerUp();
};
#endif