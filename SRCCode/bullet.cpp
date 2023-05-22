#include <SFML/Graphics.hpp>
#include "bullet.h"
#include <iostream>
Bullet::Bullet(sf::Vector2f player, int damage, float speed) {
    body = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/bullet.png");
    body->setTexture(*texture);
    body->setScale(0.1f, 0.2f);
    body->setPosition(player.x, player.y-50);
    body->setOrigin(body->getLocalBounds().width/2,body->getLocalBounds().height/2);
    fired = false;
    this->damage = damage;
    this->speed = speed;
}

Bullet::~Bullet() {
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
}

void Bullet::draw(sf::RenderWindow * win){
    win->draw(*body);
};

void Bullet::update() {
    sf::Vector2f movement;
    movement.y += speed;
    body->move(movement);
}


bool Bullet::checkOutOfBounds(sf::RenderWindow* win) {
    if (this->body->getPosition().y < 0 || this->body->getPosition().y > win->getSize().y) 
    {
        return true;
    }
    return false;
}