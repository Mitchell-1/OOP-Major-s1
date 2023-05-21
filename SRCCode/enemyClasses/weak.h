#ifndef WEAK_H
#define WEAK_H

#include "../enemy.h"

class weakEnemy: public enemy {
private:
double shootChance;

public:
weakEnemy(int len, int width, int x, int y, sf::Texture *text);
void animation(sf::Clock &clock);

};

#endif                 