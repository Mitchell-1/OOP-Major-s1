#include <SFML/Graphics.hpp>
#include "bullet.h"
#include <iostream>
Bullet::Bullet(sf::Vector2f player, int damage) {
    body = new sf::Sprite;
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/bullet.png");
    body->setTexture(*texture);
    body->setScale(0.1f, 0.2f);
    body->setPosition(player);
    body->setOrigin(body->getPosition().x/2,body->getPosition().y/2);
    fired = false;
    this->damage = damage;
}

Bullet::~Bullet() {
    delete this->body;
    delete this->texture;
    this->texture = nullptr;
    this->body = nullptr;
    std::cout << "Bullet destroyed" << std::endl;
}

void Bullet::draw(sf::RenderWindow * win){
    win->draw(*body);
};

void Bullet::update(sf::RenderWindow* win) {
    sf::Vector2f movement;
    movement.y += speed;
    body->move(movement);
    draw(win);
}


bool Bullet::checkOutOfBounds(sf::RenderWindow* win) {
    if (this->body->getPosition().y < 0) 
    {
        return true;
    }
    return false;
}