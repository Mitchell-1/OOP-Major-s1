#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "powers.h"
#include "entity.h"
#include "weapon.h"
#include "bullet.h"
#include "player.h"
#include <iostream>
#include <vector>


class enemy : public entity {
protected:
    char type;
    sf::Sprite* body;
    sf::IntRect source;
    sf::Texture* texture;
    weapon * weapon;
    double direction;
    bool texture2 = false;
    sf::Clock deathClock;
    int deathTime;
    sf::Clock hitTime;
    bool isHit = false;
    std::vector<Bullet*> bullets;
    double shootChance;
public:
virtual void die();

enemy();
enemy(int x, int y, sf::Texture *text);
void bulletValidity(sf::RenderWindow *win, std::vector<Bullet*> &enemyBullets);
void powerUpDrop();
void update(sf::RenderWindow * win, std::vector<Bullet*>& Bullets, std::vector<Bullet*> &enemyBullets);
sf::Vector2f getBody();
sf::FloatRect getGlobal();
void draw(sf::RenderWindow * win, std::vector<Bullet*> &enemyBullets);
void animation(sf::Clock &clock);
void takeDamage(int damage);
void shoot(std::vector<Bullet*> &enemyBullets);
~enemy();

};
#endif
