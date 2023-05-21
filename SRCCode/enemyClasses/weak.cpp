#include "weak.h"

weak::weak(int len, int width, int x, int y, sf::Texture *text)
{
    source = sf::IntRect(34, 2, 12, 12);
    body = new sf::Sprite();
    this->texture = new sf::Texture(*text);
    body->setTexture(*texture);
    body->setTextureRect(source);
    body->setScale(5, 5);
    body->setOrigin(body->getLocalBounds().width/2,body->getLocalBounds().height/2);
    body->setPosition(x, y);

    this-> health = 1;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 1 ;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
}

void weak::animation(sf::Clock &gameClock) {
    if (gameClock.getElapsedTime().asSeconds() >= 1 && !isDying)
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

weak::~weak()
{
    std::cout << "end Weak" << std::endl;
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
}