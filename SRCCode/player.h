#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "powers.h"
#include "entity.h"
#include "weapon.h"
#include <iostream>
#include <vector>
#include "bullet.h"
#include <iostream>
#include <memory>
using namespace std;

class Player : entity {

protected:
sf::Sprite* body;
sf::Texture* texture;
std::string classType;
std::vector<powerUp> powerUpList;
bool left;
bool right;
bool isShooting;
weapon * weapon;
int reload = 0;
std::vector<Bullet*> bullets;

public:

Player();
Player(int, int, int);
void draw(sf::RenderWindow * win);
void bulletValidity(sf::RenderWindow * win);
virtual void playerUpdate() {};
void getPowerUp(powerUp);
void removePowerUp(powerUp);

void processEvents(sf::Keyboard::Key key, bool checkPressed);
std::vector<Bullet*>& getBullets(){return this->bullets;};
void update(sf::RenderWindow* win);

void shoot();


};

#endif