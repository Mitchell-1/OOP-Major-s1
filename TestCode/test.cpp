#include "../SRCCode/game.h"
#include <string>


int main(){
game g1(1600, 900, "testGame");
int gamePasses = gameTests();
int playerPasses = playerTests();
int enemyPasses = enemyTests();

if (gamePasses == 4)
    {
        std::cout << "All Game tests passed" << std::endl;
    } else
    {
        std::cout << gamePasses << "/5 Game tests passed" << std::endl;
    }

if (playerPasses == 5)
    {
        std::cout << "All player tests passed" << std::endl;
    } else
    {
        std::cout << playerPasses << " Player tests passed" << std::endl;
    }
if (enemyPasses == 5)
    {
        std::cout << "All enemy tests passed" << std::endl;
    } else
    {
        std::cout << enemyPasses << " Enemy tests passed" << std;
    }
}

int gameTests(game testGame)
{
    int testsPassed = 0;
    int inCorr = 0;

    if (testGame.getCurrLevel() == 1);
        testsPassed++;
    else 
        std::cout << "First level loading test failed" << std::endl;
    testGame.levelManager();
    if (testGame.getCurrLevel() == 2)
        {
            std::cout << "level change system test passed" << std::endl;
            testsPassed++;
            enemy ** testLevel = game.getLevel();
            for (int i = 0; i < level1Size; i++){
                switch(level2[i])
                case: 0
                    if (testLevel[i] != nullptr)
                    {
                        inCorr++;
                    }
                    
                case: 1
                    if (enemy[i]->getType() != 'w')
                    {
                        inCorr++;
                    }
                    break;
                case: 2
                    if (enemy[i]->getType() != 's')
                    {
                        inCorr++;
                    }
                    break;
                case: 3
                if (enemy[i]->getType() != 'f')
                    {
                        inCorr++;
                    }
                    break;
                default:
                    incorr++;
            }
            if (incor == 0)
            {
                std::cout << "level loading test passed" << std::endl;
                testsPassed++;
            } else
                std::cout << "level loading test failed" << std::endl;
        } else
            std::cout << "level changing test failed" << std::endl << "Subsequently level loading test unable to run" << std::endl;

    testGame.updateDt();
    float desiredTPF = testGame.getframeCap()/testGame.getTickRate();
    if (testGame.getTPF() > desiredtpf-1 && testGame.getTPF() < desiredtpf +1)
    {   
        std::cout << "delta time test passed" << std::endl;
        testsPassed ++;
    }else;
        std::cout << "delta time test failed" << std:: endl;
}

int playerTests() 
{

}

int enemyTests()
{

}
