#include "enemy.h"


enemy::enemy() {
    this->max_health = 1;
    this->health = 1;
    this->damage = 1;
    this->speed = 1;
    this->lives = 1;
    this->tempLives = 0;
};


enemy::enemy(int len, int width, int x, int y){
    body = new sf::Sprite();
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/enemy.png");
    body->setTexture(*texture);
    body->setScale(0.2f, 1);
    body->setOrigin(len/2, width/2);
    body->setPosition(x, y);


    this->isDead = false;
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 1;
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
    if (body->getPosition().x >= win->getSize().x -10) {
        movement.y += 20;
        direction = (-0.05 * speed);
        
    } else if (body->getPosition().x <= 10) {
        movement.y += 20;
        direction = (0.05 * speed);
        
    }
    movement.x += direction;
    body->move(movement);

};

void enemy::draw(sf::RenderWindow * win){
    win->draw(*body);
};

enemy::~enemy(){
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
    //std::cout << "enemy destroyed" << std::endl;
}