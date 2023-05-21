#include "fast.h"

fastEnemy::fastEnemy(int x, int y, sf::Texture *text) : enemy(x, y, text)
{
    source = sf::IntRect(2, 18, 12, 12);
    body->setTextureRect(source);
    this->isDead = false;
    this->isDying = false;
    this->texture2 = false;
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 1 ;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
}

fastEnemy::~fastEnemy()
{
    std::cout << "end Weak" << std::endl;
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
}