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
    sf::Texture* texture;
    weapon * weapon;
    double direction;

public:
virtual void die() {};

enemy();
enemy(int len, int width, int x, int y);


void update(sf::RenderWindow * win, std::vector<Bullet*>& Bullets);
void draw(sf::RenderWindow * win);
~enemy();

};
#endif
