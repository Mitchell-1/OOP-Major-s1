#include "fast.h"


//calls the enemy constructor and sets the stats and sprites required of our "fast enemy" class
fastEnemy::fastEnemy(int x, int y, sf::Texture *text, int difficulty) : enemy(x, y, text)
{
    source = sf::IntRect(2+32, 18, 12, 12);
    body->setTextureRect(source);
    this->isDead = false;
    this->isDying = false;
    this->texture2 = false;
    this-> health = 1 * difficulty;
    this-> damage = 1 * difficulty;
    this-> speed = 10;
    this->lives = 1 *difficulty;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
    this->shootChance = 9.58/(difficulty/3);
    this->type = 'f';
}


//destroys the fast enemy the same as the enemy class
fastEnemy::~fastEnemy()
{
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
}