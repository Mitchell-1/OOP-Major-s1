#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "powers.cpp"
#include "weapon.h"
#include <iostream>
#include <vector>

using namespace std;

class player : entity {

protected:
std::string classType;
std::vector<powerUp> powerUpList;

weapon * weapon;

public:
player();
void move();

virtual void playerUpdate() {};
void getPowerUp(powerUp);
void removePowerUp(powerUp&);



};

#endif