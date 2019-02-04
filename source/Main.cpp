#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
#include "../header/Cordinates.hh"
using namespace std;



int main() 
{
    cout << "Hello, World!\n" << endl;

    BoardManager boardManager;
    boardManager.resetEverySlotAndSetSize(4);

    

    boardManager.addNewSymbol(Cordinates(3, 1), PLAYER_SYMBOL);
    boardManager.addNewSymbol(Cordinates(3, 2), PLAYER_SYMBOL);
    boardManager.addNewSymbol(Cordinates(3, 3), PLAYER_SYMBOL);
    boardManager.printBoard();

    boardManager.isBoardInWinState(3) ? cout << "znaleziono stan zwycięstwa!\n" : cout << "brak zwyciestwa...\n";

    return 0;
}

 // TODO: zaimplementować singletona! klasach Manger