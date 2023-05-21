#include "enemy.h"
#include <cmath>
#include<cstdlib>
#include "powers.h"
enemy::enemy() {
    this->max_health = 1;
    this->health = 1;
    this->damage = 1;
    this->speed = 1;
    this->lives = 1;
    this->tempLives = 0;
};


enemy::enemy(int x, int y, sf::Texture* text){
    source = sf::IntRect(34, 2, 12, 12);
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
    this-> health = 3;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 1 ;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
};

void enemy::bulletValidity(sf::RenderWindow *win, std::vector<Bullet*> &enemyBullets) 
{
    if (!enemyBullets.empty()) 
    {
            if(enemyBullets.at(0)->checkOutOfBounds(win)) /*only check first one, as it will always be the highest*/
            {
                /*remove bullet object and call destructor to free up memory*/

                delete enemyBullets.at(0);

                /*delete pointer from vector*/
                enemyBullets.erase(enemyBullets.begin());
            }           
    }
}

void enemy::update(sf::RenderWindow *win, std::vector<Bullet*> &Bullets, std::vector<Bullet*> &enemyBullets) 
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

        bulletValidity(win, enemyBullets);
    }
};

void enemy::draw(sf::RenderWindow * win, std::vector<Bullet*> &enemyBullets){
    for (int i = 0; i <enemyBullets.size(); i++)
    {
        enemyBullets.at(i)->draw(win);
    }
    win->draw(*body);

};

enemy::~enemy(){
    this->body = nullptr;
    this->texture = nullptr;
    delete this->body;
    delete this->texture;
    
};

void enemy::animation(sf::Clock &gameClock){
    if (isHit){
        if (this->hitTime.getElapsedTime().asSeconds() < 0.2)
            this->body->setColor(sf::Color::Red);
        else
        {
            this->body->setColor(sf::Color::White);
            this->isHit = false;
        }
    }
    if (gameClock.getElapsedTime().asSeconds() >= 1 && !isDying)
    {
            if(texture2)
            {   
                this->source.left -= 16;
                texture2 = false;
            }else 
            {
                this->source.left += 16;
                texture2 = true;
            }
        body->setTextureRect(source);
        
    }

    
};

void enemy::die()
{
    
    int timeDiff = deathClock.getElapsedTime().asMilliseconds() - deathTime;

    if (timeDiff < 100)
    {
        this->body->setColor(sf::Color::Red);
    }
    else if (timeDiff >= 100 && timeDiff < 200)
    {
        this->body->setColor(sf::Color::White);
    }
    else if (timeDiff >= 200 && timeDiff < 300)
    {
        body->setTextureRect(sf::IntRect(34, 18, 12, 12));
    }
    else if (timeDiff >= 300 && timeDiff < 400)
    {
        body->setScale(6, 6);
    }
    else
    {

        body->setColor(sf::Color::Black);
        this->isDead = true;
    }
    
};

void enemy::takeDamage(int damage){
    this->hitTime.restart();
    this->isHit = true;
    if (this->health <= damage) {
        if (tempLives == 0) {
            if (lives > 1)
            {
                lives --;
            }
            else 
            {
                isDying = true;
            }
        } else {
            this->tempLives --;
            this->health = max_health;
        }
    } else {
        health -= damage;

    }
}

void enemy::shoot(std::vector<Bullet*> &enemyBullets) {
    //std::cout << "shoot" << std::endl;
    std::srand((unsigned) deathClock.getElapsedTime().asMicroseconds());

    float randomGen = fmod(rand(), 13.27);//random number
    if (randomGen <= 0.02) //This number controls the amount of enemy bullets generated. the higher it is, the more bullets
    {
        randomGen += 1;/*makes only one enemy shoot every random roll*/
        Bullet* bullet = new Bullet(body->getPosition(), this->damage, 5);
        enemyBullets.push_back(bullet);
    }
    
}

void enemy::powerUpDrop() 
{
    std::srand((unsigned) std::time(NULL));

    int randomGen = rand() % 15;

    if (randomGen == 0) 
    {
        powerUp* powerup = new powerUp('h',body->getLocalBounds());
    }
}

sf::Vector2f enemy::getBody() {
    return body->getPosition();
}

sf::FloatRect enemy::getGlobal() {
    return body->getGlobalBounds();
}