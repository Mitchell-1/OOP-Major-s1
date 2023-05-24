#include "test.h"
#include "../SRCCode/levels/levels.h"

int main(){
std::cout << std::endl;
game g1(1600, 900, "testGame");
g1.gameTest();

int gamePasses = gameTests(g1);


if (gamePasses == 4)
    {
        std::cout << "All 4 Game tests passed" << std::endl << std::endl;
    } else
    {
        std::cout << gamePasses << "/4 Game tests passed" << std::endl << std::endl;
    }

int playerPasses = playerTests();

if (playerPasses == 5)
    {
        std::cout << "All player tests passed" << std::endl << std::endl;
    } else
    {
        std::cout << playerPasses << " Player tests passed" << std::endl << std::endl;
    }

int enemyPasses = enemyTests();
if (enemyPasses == 5)
    {
        std::cout << "All enemy tests passed" << std::endl << std::endl;
    } else
    {
        std::cout << enemyPasses << " Enemy tests passed" << std::endl << std::endl;
    }
}

int gameTests(game& testGame)
{
    std::cout << "Game tests" << std::endl;
    int testsPassed = 0;
    int inCorr = 0;

    if (testGame.getCurrLevel() == 1)
        testsPassed++;
    else 
        std::cout << "First level loading test failed" << std::endl;
    testGame.levelManager();
    if (testGame.getCurrLevel() == 2)
        {
            std::cout << "level change system test passed" << std::endl;
            testsPassed++;
            levelList allLevels;
            enemy ** testLevel = testGame.getLevel();
            for (int i = 0; i < 30; i++)
            {
                switch(allLevels.level2[i])
                {
                    case 0:
                        if (testLevel[i] != nullptr)
                        {
                            inCorr++;
                            
                        }
                        break;
                    case 1:
                        if (testLevel[i]->getType() != 'w')
                        {
                            inCorr++;
                        }
                        break;
                    case 2:
                        if (testLevel[i]->getType() != 's')
                        {
                            inCorr++;
                        }
                        break;
                    case 3:
                    if (testLevel[i]->getType() != 'f')
                        {
                            inCorr++;
                        }
                        break;
                    default:
                        inCorr++;
                        break;
                }
            }
            if (inCorr == 0)
            {
                std::cout << "level loading test passed" << std::endl;
                testsPassed++;
            } else
                std::cout << "level loading test failed" << std::endl;
        } else
            std::cout << "level changing test failed" << std::endl << "Subsequently level loading test unable to run" << std::endl;
    float desiredTPF = testGame.getTickRate()/(testGame.getframeCap());
    if (testGame.getTPF() > desiredTPF-1 && testGame.getTPF() < desiredTPF +1)
    {   
        std::cout << "delta time test passed" << std::endl;
        testsPassed ++;
    }else
    {
        std::cout << testGame.getTPF() << " : " << desiredTPF << std::endl;
        std::cout << "delta time test failed" << std:: endl;
    }
        return testsPassed;
};

int playerTests() 
{

    Player *player;
    player = new Player(100, 100);
    std::cout << "Player tests" << std::endl;

    int testsPassed = 0;

    std::vector<powerUp*> testPowerUps;
    powerUp* testP = new powerUp('d', player->getPosition());
    testPowerUps.push_back(testP);

    std::vector<Bullet*> testBullets;
    Bullet * testB;
    testB = new Bullet(player->getPosition(), 999, 5);
    testBullets.push_back(testB);
    player->hitReg(testBullets, testPowerUps);

    return testsPassed;
};

int enemyTests()
{
    std::cout << "Enemy tests" << std::endl;
    return 3;
    
};
