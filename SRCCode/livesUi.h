#ifndef LIVESUI_H
#define LIVESUI_H
#include <SFML/Graphics.hpp>
#include <vector>
class LivesUi {
    private:
    int lives;
    sf::Texture* texture;
    std::vector<sf::Sprite*> livesSprites;
    public:
    LivesUi();
    LivesUi(int lives, sf::Texture *text);
    void draw(sf::RenderWindow *win);
    void update(int lives);
};

#endif