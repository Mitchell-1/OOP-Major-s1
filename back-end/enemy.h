#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class enemy : public entity {
protected:
    char type;

public:
virtual void die() {};
};

#endif
