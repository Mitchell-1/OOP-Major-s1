#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "powers.h"
#include "entity.h"
#include "weapon.h"
#include "bullet.h"
#include "player.h"
#include <iostream>
#include <vector>


class enemy : public entity {
protected:
    char type;
    sf::Sprite* body;
    sf::IntRect source;
    sf::Texture* texture;
    weapon * weapon;
    double direction;
    bool texture2 = false;
    sf::Clock deathClock;
    int deathTime;
    sf::Clock hitTime;
    bool isHit = false;
public:
virtual void die();

enemy();
enemy(int len, int width, int x, int y, sf::Texture *text);


void update(sf::RenderWindow * win, std::vector<Bullet*>& Bullets);
void draw(sf::RenderWindow * win);
virtual void animation(sf::Clock &clock);
void takeDamage(int damage);
~enemy();

};
#endif
