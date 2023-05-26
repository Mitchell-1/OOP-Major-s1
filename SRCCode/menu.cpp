#include "menu.h"
#include <string>
#include <fstream>
Menu::Menu(int highScore, sf::Texture *title, sf::Texture *enter, sf::Texture *enemies, sf::Font *font)
{
    
    sf::Sprite *Title = new sf::Sprite();
    Title->setTexture(*title);
    
    sprites.push_back(Title);
    sf::Text * Enter = new sf::Text();
    Enter->setFont(*font);
    Enter->setString("PRESS ENTER");
    Enter->setFillColor(sf::Color::White);
    Enter->setCharacterSize(11);
    Enter->setScale(5,5);
    Enter->setOrigin(Enter->getLocalBounds().width/2, Enter->getLocalBounds().height/2);
    Enter->setPosition(800,530);
    texts.push_back(Enter); 

    sf::Sprite *player = new sf::Sprite();
    sf::Sprite *en2 = new sf::Sprite();

    player->setTexture(*enemies);
    player->setTextureRect(sf::IntRect(81, 16, 15, 15));
    player->setOrigin(player->getLocalBounds().width/2, player->getLocalBounds().height/2);
    player->setPosition(550, 275);
    player->setScale(7.3,7.3);
    player->setRotation(345);
    player->setColor(sf::Color::Green);
    sprites.push_back(player);


    en2->setTexture(*enemies);
    en2->setTextureRect(sf::IntRect(66, 2, 12, 12));
    en2->setOrigin(en2->getLocalBounds().width/2, en2->getLocalBounds().height/2);
    en2->setPosition(1050, 280);
    en2->setScale(8,8);
    en2->setRotation(15);
    sprites.push_back(en2);
    
    Title->setOrigin(Title->getLocalBounds().width/2, Title->getLocalBounds().height/2);
    Title->setPosition(800, 300);
    Title->setScale(10,10);


    std::ifstream scoreFile;
    scoreFile.open("SRCCode/static/score.txt");

    if (scoreFile.fail()) {
        std::cout << "no file at location" << std::endl;
    }
    if (scoreFile.is_open())
    {
        std::getline(scoreFile, this->highScore);
        std::getline(scoreFile, this->score);
        
    }
    scoreFile.close();
    

    sf::Text * highScoreText = new sf::Text();
    highScoreText->setFont(*font);
    highScoreText->setString("HIGH SCORE: " + this->highScore);
    highScoreText->setFillColor(sf::Color::White);
    highScoreText->setCharacterSize(11);
    highScoreText->setScale(3,3);
    highScoreText->setOrigin(highScoreText->getLocalBounds().width/2, highScoreText->getLocalBounds().height/2);
    highScoreText->setPosition(800,400);
    texts.push_back(highScoreText); 

    sf::Text * currentScoreText = new sf::Text();
    currentScoreText->setFont(*font);
    currentScoreText->setString("PREV SCORE: " + this->score);
    currentScoreText->setFillColor(sf::Color::White);
    currentScoreText->setCharacterSize(11);
    currentScoreText->setScale(3,3);
    currentScoreText->setOrigin(currentScoreText->getLocalBounds().width/2, currentScoreText->getLocalBounds().height/2);
    currentScoreText->setPosition(800,450);
    texts.push_back(currentScoreText); 


    /*scoreText->setString("Score: " + std::to_string(this->score));
    scoreText->setFillColor(sf::Color::White);
    scoreText->setCharacterSize(11);
    scoreText->setScale(2.5, 2.5);
    scoreText->setPosition(1300,30);*/
};

Menu::~Menu() 
{
    for (int i = 0; i <sprites.size(); i++) {
        delete sprites.at(i);
    }
    for (int i = 0; i < texts.size(); i++) {
        delete texts.at(i);
    }
    texts.clear();
    sprites.clear();
};

void Menu::update(sf::RenderWindow *win, bool &menu, sf::Clock &timer)
{
    win->clear();
    sf::Event e;
    while (win->pollEvent(e))
    {
        if (e.type == sf::Event::Closed) 
        {
            win->close();
        }
        if (e.type == sf::Event::KeyPressed)
        {
            
            if(e.key.code == sf::Keyboard::Enter)
            {
                menu = false;
                timer.restart();
            }
        }

    }
    for (int i = 0; i < sprites.size(); i++)
    {
        win->draw(*sprites.at(i));
    }
    animate();
    for (int i = 0; i < texts.size(); i++)
    {
        win->draw(*texts.at(i));
    }

    win->display();
};

void Menu::animate() 
{
    if (aniClock.getElapsedTime().asSeconds() >= 1)
    {
            if(black)
            {   
                this->texts.at(0)->setFillColor(sf::Color::Black);
                black = false;
            }else 
            {
                this->texts.at(0)->setFillColor(sf::Color::White);
                black = true;
                
            }
        aniClock.restart();
    }
    
}