#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "powers.h"
#include "entity.h"
#include "weapon.h"
#include <iostream>
#include <vector>


class enemy : public entity {
protected:
    char type;
    sf::RectangleShape* body;
    weapon * weapon;
    double direction;

public:
virtual void die() {};
enemy() {
    this->max_health = 1;
    this->health = 1;
    this->damage = 1;
    this->speed = 1;
    this->lives = 1;
    this->tempLives = 0;
};

enemy(int len, int width, int x, int y){;
    body = new sf::RectangleShape();
    body->setSize(sf::Vector2f(len, width));
    body->setPosition(x, y);
    body->setFillColor(sf::Color::Green);
    body->setOrigin(len/2, width/2);
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 1;
    this->lives = 1 ;
};


void update() 
{
    //std::cout << "update" << std::endl;
    sf::Vector2f movement;
    if (body->getPosition().x >= 400) {
        movement.y += 5;
        direction = (0.05f * speed);
        
    } else if (body->getPosition().x <= 100) {
        movement.y += 5;
        direction = (-0.05f * speed);
        
    }
    movement.x -= direction;
    body->move(movement);
};

void draw(sf::RenderWindow * win){
    win->draw(*body);
};



};
#endif

/*
unsigned short max_health;
    unsigned short health;
    unsigned short damage;
    unsigned short speed;
    unsigned short lives;
    unsigned short tempLives;
*/