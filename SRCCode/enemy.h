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
    sf::IntRect source = sf::IntRect(34, 2, 12, 12);
    sf::Texture* texture;
    weapon * weapon;
    double direction;
    bool texture2 = false;
    sf::Clock deathClock;
    int deathTime;
public:
virtual void die();

enemy();
enemy(int len, int width, int x, int y, sf::Texture *text);


void update(sf::RenderWindow * win, std::vector<Bullet*>& Bullets);
void draw(sf::RenderWindow * win);
virtual void animation(sf::Clock &clock);
~enemy();

};
#endif
