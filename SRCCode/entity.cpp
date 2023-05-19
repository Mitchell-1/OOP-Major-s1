#include "entity.h"
#include <iostream>

void entity::takeDamage(int damage){
    if (this->health <= damage) {
        if (tempLives == 0) {
            if (lives > 1)
            {
                lives --;
            }
            else 
            {
                isDead = true;
                this->health = max_health;
            }
        } else {
            this->tempLives --;
            this->health = max_health;
        }
    } else {
        health -= damage;
    }
}
