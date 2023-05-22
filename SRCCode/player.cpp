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


Player::Player(int x, int y, sf::Texture* text) {
    body = new sf::Sprite();
    this->texture = new sf::Texture(*text);
    body->setTexture(*texture);
    body->setTextureRect(sf::IntRect(51, 18, 11, 11));
    body->setScale(6,6);
    body->setPosition(x, y);
    body->setOrigin(body->getLocalBounds().width/2.f,body->getLocalBounds().height/2.f);
    body->setColor(sf::Color::Green);

    this->max_health = 1;
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 3;
    this->left = false;
    this->right = false;
    this->isShooting = false;
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

//update player position and data, with bullets encapsulated
void Player::update(sf::RenderWindow* win, std::vector<Bullet*>& Bullets) 
{
                         //check if any movement has been made
    if (isDying)
        win->close();

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

    hitReg(Bullets);

    bulletValidity(win);
    //Collision detection with screen and player

    //Left Collision
        if (body->getPosition().x - body->getGlobalBounds().width/2 < 0)
            body->setPosition(0 + (body->getGlobalBounds().width/2), body->getPosition().y);

    //Right Collision
        if (body->getPosition().x + (body->getGlobalBounds().width)/2 > win->getSize().x)
            body->setPosition(win->getSize().x - (body->getGlobalBounds().width)/2, body->getPosition().y);
};

void Player::hitReg(std::vector<Bullet*>& Bullets)
{
if (!Bullets.empty()) //checks if there are any bullets in the vector to avoid potential errors
        {
            //loops through all of the bullets in the vector and checks if the bullet collision box intersects with the enemy hitbox and if it does then it triggers takedamage()
            for (int i = 0; i < Bullets.size(); i++){ 
                if(body->getGlobalBounds().intersects(Bullets.at(i)->getRect())) 
                {
                    takeDamage(Bullets.at(i)->getDamage());
                    //deletes the bullet from memory and then erases its position from the vector 
                    delete Bullets.at(i);
                    Bullets.erase(Bullets.begin()+i);
                }  
            }          
        }
};

void Player::takeDamage(int damage) 
{
this->hitTime.restart(); //restarts the clock so that the animations can work properly
    this->isHit = true;

    //these if statements check all possibilites for taking damage and act accordingly
    if (this->health <= damage) {
        if (tempLives == 0) {
            if (lives > 1)
            {
                lives --; // reducing lives if the player has several and has too low of hp
                this->health =max_health;
            }
            else 
            {
                isDying = true; //kills the player if they don't have extra lives
            }
        } else {
            this->tempLives --; //reduces temp lives if there are any remaining
            this->health = max_health;
        }
    } else {
        health -= damage; //reduces health if there is more health than damage taken
    }
};

    //Bullet is created at runtime when space is clicked and added to bullets vector
void Player::shoot() {
        Bullet* bullet = new Bullet(body->getPosition(), this->damage, -5);
        bullets.push_back(bullet);
}


void Player::getPowerUp(powerUp power){
};

void Player::removePowerUp(powerUp power){
};


void Player::draw(sf::RenderWindow * win){
    for (int i = 0; i <bullets.size(); i++)
    {
        bullets.at(i)->draw(win);
    }
    win->draw(*body);
    
};