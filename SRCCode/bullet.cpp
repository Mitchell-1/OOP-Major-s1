#include <SFML/Graphics.hpp>
#include "bullet.h"

Bullet::Bullet(sf::Vector2f player) {
    body = new sf::RectangleShape(sf::Vector2f(5,10));
    body->setOrigin(body->getPosition().x/2,body->getPosition().y/2);
    body->setPosition(player);

    body->setFillColor(sf::Color::Yellow);
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