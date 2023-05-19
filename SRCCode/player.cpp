#include <SFML/Graphics.hpp>
#include "player.h"


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


Player::Player(int r, int x, int y) {
    body = new sf::Sprite();
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/player.png");
    body->setTexture(*texture);
    body->setScale(0.04f, 0.1f);
    body->setPosition(x, y);
    body->setOrigin(body->getPosition().x/2,body->getPosition().y/2);
    body->setColor(sf::Color::Green);

    
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 1 ;
    this->left = false;
    this->right = false;
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
            reload = 50;
        };
        }
    else {
        reload --;
    }
}

//update player position and data, with bullets encapsulated
void Player::update(sf::RenderWindow* win) 
{
                         //check if any movement has been made
    sf::Vector2f movement;
    if (left)
        movement.x -= (0.5 * speed);
    if (right)
        movement.x += (0.5 * speed);

    body->move(movement);
    /*moves bullets after being shot*/
    for (int i = 0; i < bullets.size(); i++) {
        bullets.at(i)->update(win);
    }

    bulletValidity(win);
    //Collision detection with screen and player

    //Left Collision
        if (body->getPosition().x < 0)
            body->setPosition(0, body->getPosition().y);

    //Right Collision
        if (body->getPosition().x + (body->getGlobalBounds().width) > win->getSize().x)
            body->setPosition(win->getSize().x - (body->getGlobalBounds().width), body->getPosition().y);
};



    //Bullet is created at runtime when space is clicked and added to bullets vector
void Player::shoot() {
        Bullet* bullet = new Bullet(body->getPosition(), this->damage);
        bullets.push_back(bullet);
}


void Player::getPowerUp(powerUp power){
    if (powerUpList.size() < 2){
        this-> health += power.health;
        this-> damage += power.damage;
        this-> speed += power.speed;
        this->tempLives += power.lives;
        powerUpList.push_back(power);
    };
};

void Player::removePowerUp(powerUp power){
    this-> health -= power.health;
    this-> damage -= power.damage;
    this-> speed -= power.speed;
    this->tempLives -= power.lives;
    powerUpList.erase(powerUpList.begin());
};


void Player::draw(sf::RenderWindow * win){
    win->draw(*body);
    for (int i = 0; i <bullets.size(); i++)
    {
        bullets.at(i)->draw(win);
    }
};