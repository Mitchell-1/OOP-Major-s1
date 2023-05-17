#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "powers.h"
#include "entity.h"
#include "weapon.h"
#include <iostream>
#include <vector>

using namespace std;

class Player : entity {

protected:
sf::CircleShape* body;
std::string classType;
std::vector<powerUp> powerUpList;
bool left;
bool right;
weapon * weapon;

public:
Player();
Player(int, int, int);
void move();
void draw(sf::RenderWindow * win);

virtual void playerUpdate() {};
void getPowerUp(powerUp);
void removePowerUp(powerUp);

void processEvents(sf::Keyboard::Key key, bool checkPressed) 
{
    if (checkPressed == true) 
    {
        if (key == sf::Keyboard::A) 
            left = true;
        if (key == sf::Keyboard::D) 
            right = true;
    }
    if (checkPressed == false) 
    {
        left = false, right = false;
    }
};

void update() 
{
    double move = (speed)/10;
    sf::Vector2f movement;
    if (left) 
        movement.x -= this->speed;
    if (right) 
        movement.x += this->speed;
    body->move(movement);
};


};

#endif