#ifndef POWERUPS_H
#define POWERUPS_H

powerUp healthBoost(powerUp power){
    power.name = 'h';
    power.health = 3;
    power.lives = 1;
    power.duration = 10;
    power.time = std::time(NULL);
    return power;
};

#endif