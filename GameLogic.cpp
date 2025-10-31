#include "GameLogic.h"

#include <iostream>

GameLogic::GameLogic() {}


void GameLogic::buttonPressedSlot(int i, int j){
    std::cout<<i<<" "<<j <<" "<<"is pressed "<<std::endl;
}
