#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "powers.h"
#include "entity.h"
#include "weapon.h"
#include <iostream>
#include <vector>
#include "bullet.h"
using namespace std;

class Player : entity {

protected:
sf::CircleShape* body;
std::string classType;
std::vector<powerUp> powerUpList;
std::vector<Bullet*> bullets;
bool left;
bool right;
bool isShooting;
weapon * weapon;
int reload = 500;

public:
Player();
Player(int, int, int);
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
        if (key == sf::Keyboard::Space)
            isShooting = true;
    }
    if (checkPressed == false) 
    {
        if (key == sf::Keyboard::A) 
            left = false;
        if (key == sf::Keyboard::D) 
            right = false;
        if (key == sf::Keyboard::Space)
            isShooting = false;
    }
};

void update(sf::RenderWindow* win) 
{
    sf::Vector2f movement;
    if (left)
        movement.x -= (0.05 * speed);
    if (right)
        movement.x += (0.05 * speed);

    body->move(movement);
    for (int i = 0; i < bullets.size(); i++) {
        bullets.at(i)->update(win);
    }
    
    if (reload ==0) {
        if (isShooting){
            shoot();
            reload = 5;
        };
        }
    else {
        reload --;
    }
};


void shoot() {
        Bullet* bullet = new Bullet(body->getPosition());
        bullets.push_back(bullet);
}


};

#endif