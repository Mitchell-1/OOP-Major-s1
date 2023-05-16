#include "player.h"


player::player() {
    this-> health = 1;
    this-> damage = 1;
    this-> speed = 1;
    this->lives = 1 ;
    //this-> weapon = weapon();
    //powerUpList = new powerUp[2];

};

void player::move(){

};



void player::getPowerUp(powerUp power){
    if (powerUpList.size() < 2){
        this-> health += power.health;
        this-> damage += power.damage;
        this-> speed += power.speed;
        this->tempLives += power.lives;
        powerUpList.push_back(power);
    };
};

void player::removePowerUp(powerUp &power){
    this-> health -= power.health;
    this-> damage -= power.damage;
    this-> speed -= power.speed;
    this->tempLives -= power.lives;
    delete &power;
    powerUpList.erase(powerUpList.begin());
};