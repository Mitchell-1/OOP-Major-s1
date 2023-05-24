#ifndef FAST_H
#define FAST_H

#include <cmath>
#include "enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class fastEnemy: public enemy {
private:
double shootChance;

public:
fastEnemy();
fastEnemy(int x, int y, sf::Texture *text, int difficulty);
void shoot(std::vector<Bullet*> &enemyBullets);
~fastEnemy();
};

#endif