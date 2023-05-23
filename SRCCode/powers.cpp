#include "powers.h"
#include <SFML/Graphics.hpp>
#include <iostream>
powerUp::powerUp(char classType, sf::Vector2f enemyPos){
    switch (classType) {
        case 'h':
            body = new sf::Sprite();
            this->texture = new sf::Texture();
            this->texture->loadFromFile("SRCCode/static/SpriteMap.png");
            body->setTexture(*texture);
            body->setTextureRect(sf::IntRect(18, 2, 11, 11));
            body->setScale(5,5);
            body->setPosition(enemyPos.x, enemyPos.y);
            body->setOrigin(body->getLocalBounds().width/2.f,body->getLocalBounds().height/2.f);
            this->health  = 1;
            break;
        case 'd':
            body = new sf::Sprite();
            this->texture = new sf::Texture();
            this->texture->loadFromFile("SRCCode/static/SpriteMap.png");
            body->setTexture(*texture);
            body->setTextureRect(sf::IntRect(2, 2, 11, 11));
            body->setScale(5,5);
            body->setPosition(enemyPos.x, enemyPos.y);
            body->setOrigin(body->getLocalBounds().width/2.f,body->getLocalBounds().height/2.f);
            this-> damage = 2;
            break;
        case 's':
            body = new sf::Sprite();
            this->texture = new sf::Texture();
            this->texture->loadFromFile("SRCCode/static/SpriteMap.png");
            body->setTexture(*texture);
            body->setTextureRect(sf::IntRect(2, 18, 11, 11));
            body->setScale(5,5);
            body->setPosition(enemyPos.x, enemyPos.y);
            body->setOrigin(body->getLocalBounds().width/2.f,body->getLocalBounds().height/2.f);
            this->reload = 25;
            break;
    }



}

powerUp::~powerUp() 
{
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
    this->duration = nullptr;
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
