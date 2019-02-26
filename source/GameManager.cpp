#include "../header/GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance(){
    if(instance == nullptr){
        instance = new GameManager();
    }
    return instance;
}


void GameManager::printMenu(){
    std::cout << "      Welcom in game Tic Tac Toe!\n";
    std::cout << "      MENU:\n";
    std::cout << "      1.Play\n";
    std::cout << "      2.Option\n";
    std::cout << "      3.Exit\n";
    std::cout << "      Enter choice: ";
}

const int GameManager::getPointsForVictory() const {
    return pointsForVictory;
}








