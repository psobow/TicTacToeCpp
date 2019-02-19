#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
#include "../header/Cordinates.hh"
#include "../header/MinMaxManager.hh"


int main() 
{
    std::cout << "Hello, World!\n" << std::endl;

    BoardManager *boardManager = BoardManager::getInstance();

    MinMaxManager *minMaxManager = MinMaxManager::getInstance();

    //boardManager->addNewSymbol(Cordinates(0,0), COMPUTER);
    //boardManager->addNewSymbol(Cordinates(0,1), COMPUTER);
    boardManager->addNewSymbol(Cordinates(0,2), COMPUTER);

    //boardManager->addNewSymbol(Cordinates(1,0), COMPUTER);
    //boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
    //boardManager->addNewSymbol(Cordinates(1,2), COMPUTER);

    boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
    //boardManager->addNewSymbol(Cordinates(2,1), COMPUTER);
    //boardManager->addNewSymbol(Cordinates(2,2), COMPUTER);



    boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
    //boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
    //boardManager->addNewSymbol(Cordinates(0,2), PLAYER);

    boardManager->addNewSymbol(Cordinates(1,0), PLAYER);
    boardManager->addNewSymbol(Cordinates(1,1), PLAYER);
    //boardManager->addNewSymbol(Cordinates(1,2), PLAYER);

    //boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
    //boardManager->addNewSymbol(Cordinates(2,1), PLAYER);
    //boardManager->addNewSymbol(Cordinates(2,2), PLAYER);

    boardManager->printBoard();


    //minMaxManager->mainMinMax();
    //boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
    //minMaxManager->mainMinMax();
    //boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
   // minMaxManager->mainMinMax();

    //boardManager->printBoard();


    return 0;
}
