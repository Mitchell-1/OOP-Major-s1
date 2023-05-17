#include "powers.h"

powerUp::powerUp(char classType){
    switch (classType) {
        case 'h':
            this->health  = 3;
        case 'd':
            this-> damage = 3;
        case 's':
            this->speed = 2;
    }
    

}