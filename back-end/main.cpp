#include <iostream>
#include "player.h"
#include "powerUps.cpp"

int main() {
player p1;
powerUp health;
health = healthBoost(health);
p1.getPowerUp(health);
p1.removePowerUp(&health);

}