#include <SFML/Graphics.hpp>
#include "bullet.h"
#include <iostream>


//standard constructor for the bullets. It takes a location and the damage and speed of the bullet
Bullet::Bullet(sf::Vector2f player, int damage, float speed) {

    //creating the bullet the same as the player and enemies are created
    body = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/bullet.png");
    body->setTexture(*texture);
    body->setScale(0.1f, 0.2f);
    body->setPosition(player.x, player.y-50);
    body->setOrigin(body->getLocalBounds().width/2,body->getLocalBounds().height/2);
    
    //assigning the stats for the bullets
    fired = false;
    this->damage = damage;
    this->speed = speed;
}


//deconstructor for the bullets. This deletes the bullet from the heap and from the game file
Bullet::~Bullet() {
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
}

void Bullet::draw(sf::RenderWindow * win){
    win->draw(*body);
};


//updates the bullets position
void Bullet::update() {
    sf::Vector2f movement;
    movement.y += speed;
    body->move(movement);
}

//checks if the bullets if off the screen vertically and returns true if it is
bool Bullet::checkOutOfBounds(sf::RenderWindow* win) {
    if (this->body->getPosition().y < 0 || this->body->getPosition().y > win->getSize().y) 
    {
        return true;
    }
    return false;
}