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
sf::Sprite* body;
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

                                            //script wrote to make input keys smooth and indpendently working of each other
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
        
        if (key == sf::Keyboard::A)         // --> set key once not pressed to false variable
            left = false;
        if (key == sf::Keyboard::D) 
            right = false;
        if (key == sf::Keyboard::Space)
            isShooting = false;
    }
};
                                        //update player position, data and bullets
void update(sf::RenderWindow* win) 
{
                                        //check if any movement has been made
    sf::Vector2f movement;
    if (left)
        movement.x -= (0.05 * speed);
    if (right)
        movement.x += (0.05 * speed);

    body->move(movement);
                                                //move bullets according to speed data member
    for (int i = 0; i < bullets.size(); i++) {
        bullets.at(i)->update(win);
    }
                                //capping firerate at a certian amount, and only allowing firing if the wait time is up.
    if (reload ==0) {
        if (isShooting){
            shoot();
            reload = 500;
        };
        }
    else {
        reload --;
    }

    //Collision detection with screen and player

    
    //need to fix right collision, as win->getSize().x does not stop it at the end

    //Left Collision
        if (body->getPosition().x - (body->getGlobalBounds().width/2) < 0)
            body->setPosition(0 + (body->getGlobalBounds().width/2), body->getPosition().y);

    //Right Collision
        if (body->getPosition().x + (body->getGlobalBounds().width) > win->getSize().x)
            body->setPosition(win->getSize().x - (body->getGlobalBounds().width), body->getPosition().y);
};

    //Bullet is created at runtime when space is clicked and added to bullets vector
void shoot() {
        Bullet* bullet = new Bullet(body->getPosition());
        bullets.push_back(bullet);
}


};

#endif