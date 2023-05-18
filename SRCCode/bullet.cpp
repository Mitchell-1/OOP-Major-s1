#include <SFML/Graphics.hpp>
#include "bullet.h"

Bullet::Bullet(sf::Vector2f player) {
    body = new sf::Sprite;
    sf::Texture * texture;
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/bullet.png");
    body->setTexture(*texture);
    body->setScale(0.1f, 0.2f);
    body->setOrigin(body->getPosition().x/2,body->getPosition().y/2);
    body->setPosition(player);
    fired = false;
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


//give bullets to game, have constructor grab player detail
