#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "powers.h"
#include "entity.h"
#include "weapon.h"
#include <iostream>
#include <vector>

using namespace std;

class Player : entity {

protected:
sf::CircleShape* body;
std::string classType;
std::vector<powerUp> powerUpList;

weapon * weapon;

public:
Player();
Player(int, int, int);
void move();
void draw(sf::RenderWindow * win);

virtual void playerUpdate() {};
void getPowerUp(powerUp);
void removePowerUp(powerUp);



};

#endif