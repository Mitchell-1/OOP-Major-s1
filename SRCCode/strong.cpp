#include "strong.h"


strongEnemy::strongEnemy(int x, int y, sf::Texture *text) : enemy(x, y, text)
{
    source = sf::IntRect(2, 2, 12, 12);
    body->setTextureRect(source);
    this->isDead = false;
    this->isDying = false;
    this->texture2 = false;
    this-> health = 5;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 1 ;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
}

strongEnemy::~strongEnemy()
{
    std::cout << "end strong" << std::endl;
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
}