#ifndef POWERS_H
#define POWERS_H


#include <iostream>
class powerUp {
    public:
        char name;
        unsigned short health = 0;
        unsigned short damage = 0;
        unsigned short speed = 0;
        unsigned short lives = 0;
        int time;
        int duration = 5;
        powerUp(char classType);
};

#endif