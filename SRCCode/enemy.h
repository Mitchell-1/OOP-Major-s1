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
    float shootChance;
public:
virtual void die(std::vector<powerUp*>& powerups);

enemy();
enemy(int x, int y, sf::Texture *text);
char getType() {return this->type;};
void powerUpDrop(std::vector<powerUp*> &powerups);
void update(sf::RenderWindow * win, std::vector<Bullet*>& Bullets, std::vector<powerUp*>& powerups);
sf::Vector2f getBody();
sf::FloatRect getGlobal();
void draw(sf::RenderWindow * win);
void animation(sf::Clock &clock);
void takeDamage(int damage);
void shoot(std::vector<Bullet*> &enemyBullets);
~enemy();

};
#endif
