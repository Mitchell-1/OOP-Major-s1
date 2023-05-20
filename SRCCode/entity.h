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
    bool isDying;
    bool isDead;
    void takeDamage(int damage);
};

#endif