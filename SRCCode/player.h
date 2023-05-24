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
std::vector<powerUp*> powerUpList;
bool left;
bool right;
bool isShooting;
weapon * weapon;
int maxReload = 50;
int reload = 0;
std::vector<Bullet*> bullets;
sf::Clock hitTime;
bool isHit = false;
sf::IntRect source(){return sf::IntRect(81, 16, 15, 15);};



public:
void setIsHit(bool isHit);
Player();
Player(int, int);
Player(int, int, sf::Texture* texture);
void draw(sf::RenderWindow * win);
void bulletValidity(sf::RenderWindow * win);
virtual void playerUpdate() {};
void getPowerUp(powerUp* power);
void removePowerUp(powerUp* power);

void processEvents(sf::Keyboard::Key key, bool checkPressed);
std::vector<Bullet*>& getBullets(){return this->bullets;};
void update(sf::RenderWindow* win, std::vector<Bullet*>& Bullets, std::vector<powerUp*>& currentPowerUps);
void hitReg(std::vector<Bullet*>& Bullets, std::vector<powerUp*>& currentPowerUps);
void checkPowerTime(std::vector<powerUp*>& currentPowerUps);
void takeDamage(int damage);
void shoot();
int getLives() {return this->lives;};
int getTempLives() {return this->tempLives;};
int getReload() {return this->maxReload;};
int getDamage() {return this->damage;};
bool getisDying() {return this->isDying;};
sf::Vector2f getPosition() {return this->body->getPosition();};
void animation();

};

#endif