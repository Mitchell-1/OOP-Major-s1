#include "weapon.h"


weapon::weapon(){
this-> fireRate = 1;
this-> magazine = 1;
this-> reload = 0.5;
this-> ammoCounter = 1;
this-> fireType = 's';
this-> upgradesList = new upgrade[5];
};

void weapon::getUpgrade(upgrade upgrade){
    if (upgradeCount < 5){
        this-> fireRate += upgrade.fireRate;
        this-> magazine += upgrade.magazine;
        this-> reload -= upgrade.reload;
    };

};