#include <iostream>

#include "../header/GameManager.hh"
#include "../header/GameOptionsManager.hh"

// TODO: poprawić skrypty w bashu. zrobić skrypt który skompiluje wszytko w folderze source i przeniesie to do object
 


int main() {
    std::cout << "Hello, World!\n" << std::endl;

    GameManager *gameManager = GameManager::getInstance();
    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();

    gameOptionsManager->getEnumAssignedTo('X');
    //gameManager->startGame();
    
    return 0;


}


/*
tutorial:

https://www.neverstopbuilding.com/blog/minimax

https://www.youtube.com/watch?v=STjW3eH0Cik


*/