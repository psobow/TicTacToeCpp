#include <iostream>

#include "../header/GameManager.hh"



int main() {
    GameManager *gameManager = GameManager::getInstance();
    gameManager->run();
    return 0;
}


/*
tutorial:

https://www.neverstopbuilding.com/blog/minimax

https://www.youtube.com/watch?v=STjW3eH0Cik


*/