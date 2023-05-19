#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <vector>

class Bullet 
{
    private:
        sf::Sprite* body;
        bool fired;
        float speed = -5;
        sf::Vector2f position;
        sf::Texture* texture;
        int damage;
    public:
    int getDamage() { return damage; }
    bool checkOutOfBounds(sf::RenderWindow* win);
    sf::FloatRect getRect() {return body->getGlobalBounds();}
    Bullet(sf::Vector2f playerPos, int);
    ~Bullet();
    void draw(sf::RenderWindow *win);
    void update(sf::RenderWindow *win);
};

#endif