#ifndef POWERS_H
#define POWERS_H
#include <SFML/Graphics.hpp>
#include <iostream>

class powerUp {
    private:
        sf::Sprite* body;
        sf::Texture* texture;
        bool isConsumed;
        char name;
        int time;
        float speed = 5;
        bool isActive = true;

    public:
        unsigned short health = 0;
        unsigned short damage = 0;
        unsigned short reload = 0;
        unsigned short lives = 0;
        sf::Clock* duration;
        powerUp();
        void hide();
        powerUp(char classType, sf::Vector2f enemyPos);
        sf::FloatRect getRect() {return body->getGlobalBounds();}
        void draw(sf::RenderWindow *win);
        void update();
        bool checkOutOfBounds(sf::RenderWindow *win);
        ~powerUp();
};
#endif