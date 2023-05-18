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
    sf::Texture *texture;
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/player.png");
    body->setTexture(*texture);
    body->setScale(0.04f, 0.1f);
    body->setOrigin(r/2, r/2);
    body->setPosition(x, y);
    body->setColor(sf::Color::Green);
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 1;
    this->lives = 1 ;
    this->left = false;
    this->right = false;
};




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
};