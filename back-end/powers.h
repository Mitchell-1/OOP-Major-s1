#ifndef POWERS_H
#define POWERS_H


#include <iostream>
class powerUp {
    public:
        unsigned short health = 0;
        unsigned short damage = 0;
        unsigned short speed = 0;
        unsigned short tempLives = 0;
        int time;
        int duration = 5;
        PowerUp(char);
};

#endif