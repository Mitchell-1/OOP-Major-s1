#ifndef STRONG_H
#define STRONG_H

#include "enemy.h"

class strongEnemy: public enemy {
private:

public:
strongEnemy(int x, int y, sf::Texture *text, int difficulty);

~strongEnemy();

};
#endif