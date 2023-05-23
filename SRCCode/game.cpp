#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "bullet.h"
#include "player.h"

#include <cmath>

game::game(int x, int y, std::string title) 
{
    texture = new sf::Texture;
    texture->loadFromFile("SRCCode/static/SpriteMap.png");
    player = new Player(800, 800, texture);
    win = new sf::RenderWindow(sf::VideoMode(x,y),title);
    win->setFramerateLimit(frameCap);
    levelManager();
}

game::~game(){};

void game::updateDt() 
{
    //Updates the dt (delta time) variable with the time it takes to update and render one frame
    this->dt = this->dtClock.restart().asSeconds();
    this->tpf = this->tickRate/(1/this->dt) + offset;
    this->offset = this->tpf-floor(this->tpf);
    this->tpf = floor(this->tpf);
}


//renders the game window
void game::render() 
{
    win->clear();
    
    win->display();
}


//this function updates the game every frame and incorporates delta time to update the "physics" every tick
void game::update() 
{

    // this if loop updates the level if all enemies are destroyed
    if (currentEn == 0)
    {
        levelManager();
    }

    this->updateDt();
    
    

    //this for loop runs to create the "ticks" each frame has a certain amount of ticks based upon the tickRate and frameRate as determined in the updateDt function
    for (int i = 0; i < this->tpf; i++) 
    {

    
    sf::Event e;
    
    //checks for any player input into the game such as movement or shooting
    while (win->pollEvent(e)) 
    {
        if (e.type == sf::Event::Closed) 
        {
            win->close();
        }
        if (e.type == sf::Event::KeyPressed)
            {player->processEvents(e.key.code, true);}
        if (e.type == sf::Event::KeyReleased)
            {player->processEvents(e.key.code, false);}
    }

    //updates the enemies and potentially shoots, this also checks for collisions between enemies and player bullets
    for(int i = 0; i <30; i++)
    {
        if (level[i] != nullptr)
        {
                level[i]->shoot(this->enemyBullets);
                level[i]->update(win, player->getBullets(), currentPowerUps);

            //checks if the enemy is dead and if it is then it deletes it and removes it from the enemy list
            if (level[i]->isDead)
            {
                currentEn --;
                delete level[i];
                level[i] = nullptr;
            }
        }
    }
    //updates all bullets that have been fired by the enemies
    for (int i = 0; i < enemyBullets.size(); i++) 
    {
        enemyBullets.at(i)->update();
    }
    if (!currentPowerUps.empty()) 
    {
        for (int i = 0; i < currentPowerUps.size(); i++) 
        {   
                currentPowerUps.at(i)->update();
        }
    }

    bulletValidity();
    powerValidity();
    player->update(win, enemyBullets, currentPowerUps);
    
    }
    win->clear();

    livesRender();
    player->draw(win);
    

    //this for loop draws all enemies and activates the animations
    for(int i = 0; i <30; i++)
    {
        if (level[i] != nullptr)
        {   
            level[i]->animation(gameClock);
            level[i]->draw(win);
        }
    }

    //draws all enemy sprites on the game window
    for (int i = 0; i <enemyBullets.size(); i++)
    {
        enemyBullets.at(i)->draw(win);
    }
    if (!currentPowerUps.empty()) 
    {
        for (int i=0; i < currentPowerUps.size(); i++)
        {
            currentPowerUps.at(i)->draw(win);
            
        }
    }
    //restarts the game clock responsible for the animations
    if (gameClock.getElapsedTime().asSeconds() >= 1)
        gameClock.restart();
    
    win->display();
    
}

void game::powerValidity() 
{
    if (!currentPowerUps.empty()) 
    {
            if(currentPowerUps.at(0)->checkOutOfBounds(win)) /*only check first one, as it will always be the highest*/
            {

                delete currentPowerUps.at(0);

                /*delete pointer from vector*/

                currentPowerUps.erase(currentPowerUps.begin());
            }            
    }
}

//this function creates the array of enemy objects and subclasses. It takes an array of ints and generates an object type based on the number in the array position
void game::levelCreate(int (&levelArr)[30])
{
level = new enemy*[30];
unsigned short count;
unsigned int ArrPos = 0;

//these nested for loops decide the position of the enemy objects within the game window
for (int posY = 50; posY <win->getSize().y; posY+= 200) 
{
    
    for (int posX = 50; posX < win->getSize().x; posX+= win->getSize().x/10)
    {
        if (ArrPos == 30)
            break;

        //the switch case takes the input of the array and generates an enemy type based on which number is read e.g. 1 relates to the weak enemy and 0 is a blank space
        switch (levelArr[ArrPos]) {
            case 0: 
            {
                level[ArrPos] = nullptr;
                break;
            }
            case 1: 
            {
                weakEnemy* Wen = new weakEnemy(posX, posY, this->texture, this->difficulty);
                level[ArrPos] = Wen;
                break;
            }
            case 2:
            {
                strongEnemy* Sen = new strongEnemy(posX, posY, this->texture, this->difficulty);
                level[ArrPos] = Sen;
                break;
            }
            case 3:
            {
                fastEnemy* Fen = new fastEnemy(posX, posY, this->texture, this->difficulty);
                level[ArrPos] = Fen;
                break;
            }
        }
        ArrPos++;
    }
    
}

};


//this function checks for the validity of all enemy fired bullets and removes them from the memory if they are invalid
void game::bulletValidity() 
{
    if (!this->enemyBullets.empty()) 
    {
            if(this->enemyBullets.at(0)->checkOutOfBounds(win)) /*only check first one, as it will always be the highest*/
            {
                /*remove bullet object and call destructor to free up memory*/

                delete this->enemyBullets.at(0);

                /*delete pointer from vector*/
                this->enemyBullets.erase(enemyBullets.begin());
            }           
    }
}


//this function manages which level is generated for the game
void game::levelManager() 
{   
    currentLevel++;
    // the switch case takes the variable current level and calls the level create function with the corresponding array of level
    switch (currentLevel)
    {
    case 2:
    {
        levelCreate(allLevels.level2);
        currentEn = allLevels.level2Size;
        break;
    }
    case 3:
    {
        levelCreate(allLevels.level3);
        currentEn = allLevels.level3Size;
        break;
    }
    case 4:
    {
        levelCreate(allLevels.level4);
        currentEn = allLevels.level4Size;
        break;
    }
    case 5:
    {
        levelCreate(allLevels.level5);
        currentEn = allLevels.level5Size;
        break;
    }
    case 6:
    {
        levelCreate(allLevels.level6);
        currentEn = allLevels.level6Size;
        break;
    }
    case 7:
    {
        levelCreate(allLevels.level7);
        currentEn = allLevels.level7Size;
        break;
    }
    case 8:
    {
        levelCreate(allLevels.level8);
        currentEn = allLevels.level8Size;
        break;
    }
    case 9:
    {
        levelCreate(allLevels.level9);
        currentEn = allLevels.level9Size;
        break;
    }
    default:
    {
        currentLevel = 1;
        difficulty ++;
        levelCreate(allLevels.level1);
        currentEn = allLevels.level1Size;
        break;
    }
    }
}

void game::livesRender(){
    for (int i = 0; i < player->getLives(); i++)
    {

    }

};
//this function runs the game and loops it until the player closes the window
void game::run() {

    while (win->isOpen()) 
    {   
        this->update();
    }
}


void game::gameTest()
{
    win->close();
}