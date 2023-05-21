#include "powers.h"
#include <SFML/Graphics.hpp>
powerUp::powerUp(char classType, sf::FloatRect enemyPos){
    switch (classType) {
        case 'h':
            this->health  = 3;
        case 'd':
            this-> damage = 3;
        case 's':
            this->speed = 2;
    }
    body = new sf::Sprite();
    this->texture = new sf::Texture();
    this->texture->loadFromFile("./static/bullet.png");
    body->setTexture(*texture);
    body->setScale(1,1);
    body->setPosition(enemyPos.width/2, enemyPos.height/2);
    body->setOrigin(body->getLocalBounds().width/2.f,body->getLocalBounds().height/2.f);
    body->setColor(sf::Color::Green);

}

powerUp::~powerUp() 
{
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
};

void powerUp::draw(sf::RenderWindow *win) 
{
    win->draw(*body);
}; 


void powerUp::update() 
{
    sf::Vector2f movement;
    movement.y += speed;
    body->move(movement);
};

bool powerUp::checkOutOfBounds(sf::RenderWindow *win) 
{
    if (this->body->getPosition().y > win->getSize().y) 
    {
        return true;
    }
    return false;
};