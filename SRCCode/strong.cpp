#include "strong.h"

//calls the enemy constructor and sets the stats and sprites required of our "strong enemy" class
strongEnemy::strongEnemy(int x, int y, sf::Texture *text, int difficulty) : enemy(x, y, text)
{
    source = sf::IntRect(2+32, 2, 12, 12);
    body->setTextureRect(source);
    this->isDead = false;
    this->isDying = false;
    this->texture2 = false;
    this-> health = 2 * difficulty;
    this-> damage = 1 * difficulty;
    this-> speed = 10;
    this->lives = 1;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
    this->shootChance = 13.87;
    this->type = 's';
}

//destroys the strong enemy the same as the enemy class
strongEnemy::~strongEnemy()
{
    std::cout << "end strong" << std::endl;
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
}