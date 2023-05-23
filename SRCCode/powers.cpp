#include "powers.h"
#include <SFML/Graphics.hpp>
#include <iostream>
powerUp::powerUp(char classType, sf::Vector2f enemyPos){
    switch (classType) {
        case 'h':
            this->health  = 1;
            break;
        case 'd':
            this-> damage = 2;
            break;
        case 's':
            this->reload = 25;
            break;
    }
    body = new sf::Sprite();
    this->texture = new sf::Texture();
    this->texture->loadFromFile("SRCCode/static/bullet.png");
    body->setTexture(*texture);
    body->setScale(1,1);
    body->setPosition(enemyPos.x, enemyPos.y);
    body->setOrigin(body->getLocalBounds().width/2.f,body->getLocalBounds().height/2.f);
    body->setColor(sf::Color::Green);

}

powerUp::~powerUp() 
{
    delete this->body;
    delete this->texture;
    delete this->duration;
    this->texture = nullptr;
    this->body = nullptr;
    
    
};

void powerUp::draw(sf::RenderWindow *win) 
{
    if (isActive)
        win->draw(*body);
}; 

void powerUp::hide() 
{
    this->isActive = false;
}

void powerUp::update() 
{
    if (isActive) 
    {
        sf::Vector2f movement;
        movement.y += speed;
        body->move(movement);
    }


};

bool powerUp::checkOutOfBounds(sf::RenderWindow *win) 
{
    if (this->body->getPosition().y > win->getSize().y) 
    {
        return true;
    }
    return false;
};
