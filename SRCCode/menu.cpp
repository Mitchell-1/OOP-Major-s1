#include "menu.h"
Menu::Menu(int highScore, sf::Texture *title, sf::Texture *enter, sf::Texture *enemies)
{
    std::cout << "Menu" << std::endl;
    sf::Sprite *Title = new sf::Sprite();
    Title->setTexture(*title);
    
    sprites.push_back(Title);
    sf::Sprite *Enter = new sf::Sprite();
    Enter->setTexture(*enter);
    sprites.push_back(Enter);
    sf::Sprite *player = new sf::Sprite();
    sf::Sprite *en2 = new sf::Sprite();
    player->setTexture(*enemies);
    player->setTextureRect(sf::IntRect(81, 16, 15, 15));
    sprites.push_back(player);
    en2->setTexture(*enemies);
    en2->setTextureRect(sf::IntRect(66, 2, 12, 12));
    sprites.push_back(en2);
    
    Title->setPosition(100, 100);
    Enter->setPosition(200, 100);
    player->setPosition(300, 100);
    en2->setPosition(400, 100);
};

void Menu::update(sf::RenderWindow *win, bool &menu, sf::Clock &timer)
{
    win->clear();
    sf::Event e;
    while (win->pollEvent(e))
    {
        if (e.type == sf::Event::KeyPressed)
        {
            if(e.key.code == sf::Keyboard::Enter)
            {
                std::cout << "Enter" << std::endl;
                menu = false;
                timer.restart();
            }
        }

    }
    for (int i = 0; i < sprites.size(); i++)
    {
        win->draw(*sprites.at(i));
    }
    win->display();
};