#include "enemy.h"
#include <cmath>
#include<cstdlib>
#include "powers.h"


/*
enemy constructor function, it takes two point arguments which position it within the game window and the third argument is a sprite map which gets resized for the basic enemy object
This constructor function creates a body and assigns a texture then sets the position and origin of the body
*/
enemy::enemy(int x, int y, sf::Texture* text){
    source = sf::IntRect(34, 2, 12, 12); // creates the rectangle which will resize the texture map
    body = new sf::Sprite(); // creats the body
    this->texture = new sf::Texture(*text); // creates the new texture
    body->setTexture(*texture); // assign the texture to the body
    body->setTextureRect(source); //assigns the correct 
    body->setScale(5, 5); //scales the texture

    //sets origin and position of the body
    body->setOrigin(body->getLocalBounds().width/2,body->getLocalBounds().height/2);
    body->setPosition(x, y);


    //assigns the necessary game stats for the enemy object
    this->isDead = false;
    this->isDying = false;
    this->texture2 = false;
    this-> health = 3;
    this-> damage = 1;
    this-> speed = 10;
    this->lives = 1 ;
    this->tempLives = 0;
    this->direction = (0.05f * this->speed);
    this->shootChance = 13.87;
};



/*
this function updates the enemy and is written to be able to update inherited classes of enemy
This function takes the game window and all bullets created by the player
*/
void enemy::update(sf::RenderWindow *win, std::vector<Bullet*> &Bullets) 
{
    //checks if the enemy is dying or not and if it is, rather than updating it triggers the death function
    if (isDying) 
    { 
        die();
    }
    else
    {
        // this loop checks if this enemy is colliding with any of the bullets that the player has fired
        if (!Bullets.empty()) //checks if there are any bullets in the vector to avoid potential errors
        {
            //loops through all of the bullets in the vector and checks if the bullet collision box intersects with the enemy hitbox and if it does then it triggers takedamage()
            for (int i = 0; i < Bullets.size(); i++){ 
                if(body->getGlobalBounds().intersects(Bullets.at(i)->getRect())) 
                {
                    takeDamage(Bullets.at(i)->getDamage());
                    if (isDying) //if take damage results in the players death it records the time
                        deathTime = deathClock.getElapsedTime().asMilliseconds();
                    //deletes the bullet from memory and then erases its position from the vector 
                    delete Bullets.at(i);
                    Bullets.erase(Bullets.begin()+i);
                }  
            }          
        }

        //these if statements handle the enemies movement. If the enemy collides with either side of the screen it moves down and then flips the direction
        sf::Vector2f movement;

        //right collision
        if (body->getPosition().x >= win->getSize().x -(body->getGlobalBounds().width/2)) {
            movement.y += body->getGlobalBounds().height + 5;
            direction = (-0.05 * speed);

        //left collision            
        } else if (body->getPosition().x - (body->getGlobalBounds().width/2)<= 0) {
            movement.y += body->getGlobalBounds().height + 5;
            direction = (0.05 * speed);
            
        }
        //updating the enemies position
        movement.x += direction;
        body->move(movement);
    }
};

// this function takes the input of the game window and draws the enemies body on the screen
void enemy::draw(sf::RenderWindow * win){
    win->draw(*body);
};



enemy::~enemy(){
    //clearing the body and texture data from the heap and replaces it with a null pointer to delete easier
    this->body = nullptr; 
    this->texture = nullptr;

    //deletes the body and texture removing it from the game entirely
    delete this->body;
    delete this->texture;
    
};


//this functions takes the input of a clock and processes the animations based on the time passed
void enemy::animation(sf::Clock &gameClock){
    
    //checks if the enemy is hit and if it has been less than 0.2 seconds it will flash red else it will stay white
    if (isHit){
        if (this->hitTime.getElapsedTime().asSeconds() < 0.2)
            this->body->setColor(sf::Color::Red);
        else
        {
            this->body->setColor(sf::Color::White);
            this->isHit = false;
        }
    }

    // this section flips between the 2 animation frames every second given the enemy is not dying
    if (gameClock.getElapsedTime().asSeconds() >= 1 && !isDying)
    {
            if(texture2)
            {   
                this->source.left -= 16;
                texture2 = false;
            }else 
            {
                this->source.left += 16;
                texture2 = true;
            }
        body->setTextureRect(source);
        
    }

    
};


//this death function handles the animations and colour updates once the enemy is dead
void enemy::die()
{
    
    int timeDiff = deathClock.getElapsedTime().asMilliseconds() - deathTime;

    //these if statements create effects for the enemy depending on how long it has been since it "died" such as setting the colour or showing an explosion effect
    if (timeDiff < 100)
    {
        this->body->setColor(sf::Color::Red);
    }
    else if (timeDiff >= 100 && timeDiff < 200)
    {
        this->body->setColor(sf::Color::White);
    }
    else if (timeDiff >= 200 && timeDiff < 300)
    {
        body->setTextureRect(sf::IntRect(34, 18, 12, 12));
    }
    else if (timeDiff >= 300 && timeDiff < 400)
    {
        body->setScale(6, 6);
    }
    else
    {

        body->setColor(sf::Color::Black);
        this->isDead = true;
    }
    
};


//this function handles the damage taken by the enemy
void enemy::takeDamage(int damage){
    this->hitTime.restart(); //restarts the clock so that the animations can work properly
    this->isHit = true;

    //these if statements check all possibilites for taking damage and act accordingly
    if (this->health <= damage) {
        if (tempLives == 0) {
            if (lives > 1)
            {
                lives --; // reducing lives if the enemy has several and has too low of hp
                this->health =max_health;
            }
            else 
            {
                isDying = true; //kills the enemy if they don't have extra lives
            }
        } else {
            this->tempLives --; //reduces temp lives if there are any remaining
            this->health = max_health;
        }
    } else {
        health -= damage; //reduces health if there is more health than damage taken

    }
}

//this function generates a bullet based on a random amount of time so that the enemy's shooting is unpredictable
void enemy::shoot(std::vector<Bullet*> &enemyBullets) {
    std::srand((unsigned) deathClock.getElapsedTime().asMicroseconds()); //generates a random number seed

    float randomGen = fmod(rand(), shootChance);//random number based on seed is modulused with the shootChance and will be checked if low enough
    if (randomGen <= 0.02) //This number controls the amount of enemy bullets generated. the higher it is, the more bullets as the requirement is easier
    {
        randomGen += 1;/*makes only one enemy shoot every random roll*/
        Bullet* bullet = new Bullet(body->getPosition(), this->damage, 5); //creates the new bullet
        enemyBullets.push_back(bullet); //adds the bullet to the vector of all enemy bullets in the game
    }
    
}

void enemy::powerUpDrop() 
{
    std::srand((unsigned) std::time(NULL));

    int randomGen = rand() % 15;

    if (randomGen == 0) 
    {
        powerUp* powerup = new powerUp('h',body->getLocalBounds());
    }
}

sf::Vector2f enemy::getBody() {
    return body->getPosition();
}

sf::FloatRect enemy::getGlobal() {
    return body->getGlobalBounds();
}