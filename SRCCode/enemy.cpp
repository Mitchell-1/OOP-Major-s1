#include "enemy.h"
#include <cmath>

enemy::enemy() {
    this->max_health = 1;
    this->health = 1;
    this->damage = 1;
    this->speed = 1;
    this->lives = 1;
    this->tempLives = 0;
};


enemy::enemy(int len, int width, int x, int y, sf::Texture* text){
    body = new sf::Sprite();
    this->texture = new sf::Texture(*text);
    body->setTexture(*texture);
    body->setTextureRect(source);
    body->setScale(5, 5);
    body->setOrigin(body->getLocalBounds().width/2,body->getLocalBounds().height/2);
    body->setPosition(x, y);


    this->isDead = false;
    this->isDying = false;
    this->texture2 = false;
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 1 ;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
};



void enemy::update(sf::RenderWindow *win, std::vector<Bullet*> &Bullets) 
{
    if (isDying) 
    { 
        die();
    }
    else
    {
        if (!Bullets.empty()) 
        {
            for (int i = 0; i < Bullets.size(); i++){
                if(body->getGlobalBounds().intersects(Bullets.at(i)->getRect())) 
                {
                    takeDamage(Bullets.at(i)->getDamage());
                    if (isDying)
                        deathTime = deathClock.getElapsedTime().asMilliseconds();
                    delete Bullets.at(i);
                    Bullets.erase(Bullets.begin()+i);
                }  
            }          
        }
        sf::Vector2f movement;
        if (body->getPosition().x >= win->getSize().x -(body->getGlobalBounds().width/2)) {
            movement.y += body->getGlobalBounds().height + 5;
            direction = (-0.05 * speed);
            
        } else if (body->getPosition().x-body->getGlobalBounds().width <= 0) {
            movement.y += body->getGlobalBounds().height + 5;
            direction = (0.05 * speed);
            
        }
        movement.x += direction;
        body->move(movement);
    }
};

void enemy::draw(sf::RenderWindow * win){
    win->draw(*body);
};

enemy::~enemy(){
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
};

void enemy::animation(sf::Clock gameClock){
    if (gameClock.getElapsedTime().asSeconds() >= 1)
    {
            if(texture2)
            {   
                this->source.left = 34;
                texture2 = false;
            }else 
            {
                this->source.left = 50;
                texture2 = true;
            }
        body->setTextureRect(source);

        
    }

    
};

void enemy::die()
{
    
    int timeDiff = deathClock.getElapsedTime().asMilliseconds() - deathTime;

    if (timeDiff < 1000)
    {
        this->body->setColor(sf::Color::Red);
    }
    else if (timeDiff >= 1000 && timeDiff < 3000)
    {
        this->body->setColor(sf::Color::Green);
    }
    else if (timeDiff >= 3000 && timeDiff < 4000)
    {
        body->setTextureRect(sf::IntRect(34, 18, 12, 12));
    }
    else if (timeDiff >= 4000 && timeDiff < 5000)
    {
        body->setScale(6, 6);
    }
    else
    {
        this->isDead = true;
    }
    
};