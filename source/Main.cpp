#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
#include "../header/Cordinates.hh"
using namespace std;



int main() 
{
    cout << "Hello, World!\n" << endl;

    BoardManager boardManager = *BoardManager::getInstance();
    boardManager.resetEverySlotAndSetSize(4);

    

    boardManager.addNewSymbol(Cordinates(0, 0), PLAYER);
    boardManager.addNewSymbol(Cordinates(1, 1), PLAYER);
    boardManager.addNewSymbol(Cordinates(2, 2), PLAYER);
    boardManager.printBoard();

    boardManager.isBoardInWinState(3);

    return 0;
}
