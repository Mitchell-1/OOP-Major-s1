#ifndef ENTITY_H
#define ENTITY_H


class entity {
protected:
    unsigned short max_health;
    unsigned short health;
    unsigned short damage;
    unsigned short speed;
    unsigned short lives;
    unsigned short tempLives;

public:
    void takeDamage(int damage);
    virtual void shoot(){};
};

#endif