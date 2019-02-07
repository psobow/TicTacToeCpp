#include "../header/GameManager.hh"

GameManager* GameManager::instance = 0;

GameManager* GameManager::getInstance(){
    if(instance == 0){
        instance = new GameManager();
    }
    return instance;
}

GameManager::GameManager() {}
GameManager::~GameManager(){}

void GameManager::printMenu(){
    std::cout << "      Welcom in game Tic Tac Toe!\n";
    std::cout << "      MENU:\n";
    std::cout << "      1.Play\n";
    std::cout << "      2.Option\n";
    std::cout << "      3.Exit\n";
    std::cout << "      Enter choice: ";
}








