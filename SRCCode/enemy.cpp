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

    if (!Bullets.empty()) 
    {
        for (int i = 0; i < Bullets.size(); i++){
            if(body->getGlobalBounds().intersects(Bullets.at(i)->getRect())) 
            {
                takeDamage(Bullets.at(i)->getDamage());
                delete Bullets.at(i);
                Bullets.erase(Bullets.begin()+i);
            }  
        }          
    }
    //std::cout << "update" << std::endl;
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

};

void enemy::draw(sf::RenderWindow * win, sf::Clock gameClock){
    /*if (gameClock.getElapsedTime().asMilliseconds()%500 ==0)
    {
        changeTexture();
    }*/
    
    animation(gameClock);
    //body->setTextureRect(sf::IntRect(2, 2, 12, 12))
    win->draw(*body);
};

enemy::~enemy(){
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
    //std::cout << "enemy destroyed" << std::endl;
};

void enemy::animation(sf::Clock gameClock){

    if (gameClock.getElapsedTime().asMilliseconds()%500 <= 0.00001) {
        
    
        if(texture2)
        {   
            std::cout << "changed to texture 1" << std::endl;
            this->source.left = 34;
            texture2 = false;
        }else 
        {
            std::cout << "changed to texture 2" << std::endl;
            this->source.left = 2;
            texture2 = true;
        }
    }
    //std::cout << source.left << std::endl;
    body->setTextureRect(source);
        //std::cout << "change texture" << std::endl;
};