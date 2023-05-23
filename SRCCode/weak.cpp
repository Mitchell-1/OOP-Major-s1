#include "weak.h"
#include "enemy.h"
//calls the enemy constructor and sets the stats and sprites required of our "weak enemy" class
weakEnemy::weakEnemy(int x, int y, sf::Texture *text, int difficulty) : enemy(x, y, text)
{
    source = sf::IntRect(34+32, 2, 12, 12);
    body->setTextureRect(source);
    this->isDead = false;
    this->isDying = false;
    this->texture2 = false;
    this-> health = 1 * difficulty;
    this-> damage = 1 * difficulty;
    this-> speed = 10 ;
    this->lives = 1;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
    this->shootChance = 13.87;
    this->type = 'w';
}

//destroys the weak enemy the same as the enemy class
weakEnemy::~weakEnemy()
{
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
}

//enemy constuctor use din weak constructor
//take texture and sprite assignment awawy from enemy
//give to inherited classes
