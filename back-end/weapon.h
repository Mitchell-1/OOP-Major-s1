#ifndef WEAPON_H
#define WEAPON_H


#include "upgrades.cpp"

class weapon {
protected:
char name;
unsigned short fireRate;
unsigned short magazine;
unsigned short reload;
unsigned short ammoCount;
unsigned short upgradeCount;
char fireType;
public:
virtual void switchFireType();
void getUpgrade(upgrades);
upgrades * upgradesList;
};
#endif

