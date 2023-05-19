#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <vector>

class Bullet 
{
    private:
        sf::Sprite* body;
        bool fired;
        float speed = -0.1;
        sf::Vector2f position;
        sf::Texture* texture;
    public:
    bool checkOutOfBounds(sf::RenderWindow* win);
    Bullet(sf::Vector2f playerPos);
    ~Bullet();
    void draw(sf::RenderWindow *win);
    void update(sf::RenderWindow *win);
};

#endif