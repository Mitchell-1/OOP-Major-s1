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
    this->lives = 1;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
    this->shootChance = 4.28/(difficulty);
    this->type = 'f';
}


void fastEnemy::shoot(std::vector<Bullet*> &enemyBullets) {
    std::srand((unsigned) deathClock.getElapsedTime().asMicroseconds()); //generates a random number seed

    float randomGen = fmod(rand(), shootChance);//random number based on seed is modulused with the shootChance and will be checked if low enough
    if (randomGen <= 0.02) //This number controls the amount of enemy bullets generated. the higher it is, the more bullets as the requirement is easier
    {
        randomGen += 1;/*makes only one enemy shoot every random roll*/
        Bullet* bullet = new Bullet(body->getPosition(), this->damage, 5); //creates the new bullet
        enemyBullets.push_back(bullet); //adds the bullet to the vector of all enemy bullets in the game
    }
    
}

//destroys the fast enemy the same as the enemy class
fastEnemy::~fastEnemy()
{
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
}