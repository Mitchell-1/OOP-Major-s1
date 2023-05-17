#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class enemy : public entity {
protected:
    char type;

public:
virtual void die() {};
enemy() {
    this->max_health = 1;
    this->health = 1;
    this->damage = 1;
    this->speed = 1;
    this->lives = 1;
    this->tempLives = 0;
};
};

#endif

/*
unsigned short max_health;
    unsigned short health;
    unsigned short damage;
    unsigned short speed;
    unsigned short lives;
    unsigned short tempLives;
*/