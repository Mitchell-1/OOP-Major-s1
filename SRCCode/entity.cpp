#include "entity.h"

void entity::takeDamage(int damage){
    if (this->health <= damage) {
        if (tempLives == 0) {
            lives --;
            this->health = max_health;
        } else {
            this->tempLives --;
            this->health = max_health;
        }
    }
}
