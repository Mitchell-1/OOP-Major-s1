#ifndef STATES_H
#define STATES_H
#include <SFML/Graphics.hpp>
#include <string>
#include "bullet.h"
#include "player.h"
#include <iostream>

class State {
    private:
    sf::RenderWindow* window;
    std::vector<sf::Texture*> stateTextures;
    bool quit;
    public:
    State(sf::RenderWindow* window);
    virtual ~State();
    virtual void updateKeybinds(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    virtual void checkForQuit();
    virtual void endState() = 0;
    const bool& getQuit() const;
};

#endif