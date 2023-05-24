#include <SFML/Graphics.hpp>
#include "player.h"
#include <fstream>

Player::Player() {
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 1;
    this->lives = 1 ;
    this->left = false;
    this->right = false;
    //this-> weapon = weapon();
    //powerUpList = new powerUp[2];

};

Player::Player(int x, int y){
    body = new sf::Sprite();
    body->setTextureRect(this->source());
    body->setScale(6,6);
    body->setPosition(x, y);
    this->max_health = 1;
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 3;
    this->left = false;
    this->right = false;
    this->isShooting = false;
    this->tempLives = 0;
}

Player::Player(int x, int y, sf::Texture* text) {
    body = new sf::Sprite();
    this->texture = new sf::Texture(*text);
    body->setTexture(*texture);
    body->setTextureRect(this->source());
    body->setScale(5,5);
    body->setPosition(x, y);
    body->setOrigin(body->getLocalBounds().width/2.f,body->getLocalBounds().height/2.f);
    body->setColor(sf::Color::Green);

    this->tempLives = 0;
    this->max_health = 1;
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 5;
    this->left = false;
    this->right = false;
    this->isShooting = false;
    this->isDying = false;
};


                                            //script wrote to make input keys smooth and indpendently working of each other
void Player::processEvents(sf::Keyboard::Key key, bool checkPressed) 
{
    if (checkPressed == true) 
    {
        if (key == sf::Keyboard::A) 
            left = true;
        if (key == sf::Keyboard::D) 
            right = true;
        if (key == sf::Keyboard::Space)
            isShooting = true;
    }
    if (checkPressed == false) 
    {
        
        if (key == sf::Keyboard::A)         // --> set key once not pressed to false variable
            left = false;
        if (key == sf::Keyboard::D) 
            right = false;
        if (key == sf::Keyboard::Space)
            isShooting = false;
    }
};



void Player::bulletValidity(sf::RenderWindow* win) 
{
    /*This loop checks that bullets are on screen, and if they are not, deletes them to free up memory*/

    if (!bullets.empty()) 
    {
            if(bullets.at(0)->checkOutOfBounds(win)) /*only check first one, as it will always be the highest*/
            {
                /*remove bullet object and call destructor to free up memory*/

                delete bullets.at(0);

                /*delete pointer from vector*/

                bullets.erase(bullets.begin());
            }            
    }

    /*capping firerate at a certian amount, and only allowing firing if the wait time is up.*/
    if (reload ==0) {
        if (isShooting){
            shoot();
            reload = maxReload;
        };
        }
    else {
        reload --;
    }
}

void Player::animation()
{
    if (this->hitTime.getElapsedTime().asSeconds() <= 0.8)
    {
        this->body->setColor(sf::Color::Red);
    } else
    {
        this->isHit = false;
        this->body->setColor(sf::Color::Green);
    }
};

//update player position and data, with bullets encapsulated
void Player::update(sf::RenderWindow* win, std::vector<Bullet*>& Bullets, std::vector<powerUp*>& currentPowerUps) 
{
                         //check if any movement has been made
    if (isDying)
    {
        
    }
    if (isHit)
        animation();
    sf::Vector2f movement;
    if (left)
        movement.x -= (0.5 * speed);
    if (right)
        movement.x += (0.5 * speed);

    body->move(movement);
    /*moves bullets after being shot*/
    for (int i = 0; i < bullets.size(); i++) {
        bullets.at(i)->update();
    }

    hitReg(Bullets, currentPowerUps);

    bulletValidity(win);

    checkPowerTime(currentPowerUps);
    //Collision detection with screen and player

    //Left Collision
        if (body->getPosition().x - body->getGlobalBounds().width/2 < 0)
            body->setPosition(0 + (body->getGlobalBounds().width/2), body->getPosition().y);

    //Right Collision
        if (body->getPosition().x + (body->getGlobalBounds().width)/2 > win->getSize().x)
            body->setPosition(win->getSize().x - (body->getGlobalBounds().width)/2, body->getPosition().y);

    //check if shield

    if (tempLives >= 1) 
    {
        body->setTextureRect(sf::IntRect(17, 17, 15, 15));
    }
    else 
    {
        body->setTextureRect(this->source());
    }

    
};

void Player::hitReg(std::vector<Bullet*>& enemyBullets, std::vector<powerUp*>& currentPowerUps)
{
    if (!isHit)
    {
        if (!enemyBullets.empty()) //checks if there are any Bullets in the vector to avoid potential errors
        {
            //loops through all of the enemyBullets in the vector and checks if the bullet collision box intersects with the enemy hitbox and if it does then it triggers takedamage()
            for (int i = 0; i < enemyBullets.size(); i++){ 
                if(body->getGlobalBounds().intersects(enemyBullets.at(i)->getRect())) 
                {

                    takeDamage(enemyBullets.at(i)->getDamage());
                    //deletes the bullet from memory and then erases the pointer at its position from the vector 
                    delete enemyBullets.at(i);
                    enemyBullets.erase(enemyBullets.begin()+i);
                }  
            }          
        }
    }
        if (!currentPowerUps.empty()) 
        {
            for (int i = 0; i < currentPowerUps.size(); i++) 
            {
                if (body->getGlobalBounds().intersects(currentPowerUps.at(i)->getRect())) 
                {
                    powerUp *powerUpP;
                    powerUpP = currentPowerUps.at(i);
                    getPowerUp(currentPowerUps.at(i));
                    currentPowerUps.at(i)->hide();
                    currentPowerUps.erase(currentPowerUps.begin()+i);
                }
            }
        }
};

void Player::takeDamage(int damage) 
{
    this->hitTime.restart(); //restarts the clock so that the animations can work properly
    this->isHit = true;

    //these if statements check all possibilites for taking damage and act accordingly
    if (this->health <= this->damage) {
        if (this->tempLives == 0) {
            if (this->lives > 1)
            {

                this->lives --; // reducing lives if the player has several and has too low of hp
                this->health =max_health;
            }
            else 
            {

                this->isDying = true; //kills the player if they don't have extra lives
            }
        } else {

            this->tempLives --; //reduces temp lives if there are any remaining
            this->health = max_health;
        }
    } else {

        this->health -= damage; //reduces health if there is more health than damage taken
    }
};

    //Bullet is created at runtime when space is clicked and added to bullets vector
void Player::shoot() {
        Bullet* bullet = new Bullet(body->getPosition(), this->damage, -7.5);
        bullets.push_back(bullet);
}


void Player::getPowerUp(powerUp* power){
    powerUpList.push_back(power);
    this->tempLives += power->health;
    if (this->maxReload < power->reload)
    {
        maxReload = 1;
    } else 
        this->maxReload -= power->reload;
    this->damage += power->damage;
    sf::Clock* time = new sf::Clock;
    power->duration = time;
};

void Player::removePowerUp(powerUp* power){
        if (tempLives != 0)
            this->tempLives -= power->health;
        if (power->damage < this->damage)
            this->damage -= power->damage;
        if (power->reload + this->maxReload <= 50)
        {
            this->maxReload += power->reload;
        } else 
        {
            this->maxReload = 50;
        }
        delete power->duration;
        delete power;
};


void Player::draw(sf::RenderWindow * win){
    for (int i = 0; i <bullets.size(); i++)
    {
        bullets.at(i)->draw(win);
    }
    win->draw(*body);
    
};

void Player::checkPowerTime(std::vector<powerUp*>& currentPowerUps) 
{
    if (!powerUpList.empty()) 
    {
        for (int i = 0; i < powerUpList.size(); i++) 
        {
            if (powerUpList.at(i)->duration->getElapsedTime().asMicroseconds() >= 7500000) 
            {
                this->removePowerUp(powerUpList.at(i));
                powerUpList.erase(powerUpList.begin());
            }
        }

    }
}