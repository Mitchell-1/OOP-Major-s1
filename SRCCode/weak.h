#ifndef WEAK_H
#define WEAK_H

#include "enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class weakEnemy: public enemy {
private:
double shootChance;

public:
weakEnemy();
weakEnemy(int x, int y, sf::Texture *text);

~weakEnemy();
};

#endif                 