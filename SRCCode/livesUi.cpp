#include "livesUi.h"



LivesUi::LivesUi(int lives, sf::Texture *text) : lives(lives) 
{
    for (int i = 0; i < lives; i++) 
    {
        sf::Sprite *body = new sf::Sprite();
        this->texture = new sf::Texture(*text);
        body->setTexture(*texture);
        body->setTextureRect(sf::IntRect(80, 17, 15, 15));
        body->setColor(sf::Color::Green);
        body->setScale(3.5,3.5);
        livesSprites.push_back(body);
    }


};

void LivesUi::draw(sf::RenderWindow *win) 
{
    for (int i = 0; i < livesSprites.size(); i++) 
    {
        win->draw(*livesSprites.at(i));
    }
}

void LivesUi::update(int lives) 
{
    this->lives = lives;
    if (!livesSprites.empty()) {
    while (this->lives < livesSprites.size()) 
    {
        delete livesSprites.at(0);
        livesSprites.erase(livesSprites.begin());
    }
    for (int i = 0; i < this->lives; i++) 
    {
        livesSprites.at(i)->setPosition(20+(50*i),30);
    }
}
}