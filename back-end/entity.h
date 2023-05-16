#ifndef ENTITY_H
#define ENTITY_H


class entity {
protected:
    unsigned short health;
    unsigned short damage;
    unsigned short speed;
    unsigned short lives;
    unsigned short tempLives;

public:
    virtual void takeDamage(unsigned short damage) {};
    virtual void shoot(){};
};

#endif