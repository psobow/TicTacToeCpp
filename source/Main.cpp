#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
#include "../header/Cordinates.hh"
using namespace std;



int main() 
{
    cout << "Hello, World!\n" << endl;

    BoardManager boardManager;
    boardManager.printBoard();

    boardManager.resetEverySlotAndSetSize(2);
    boardManager.printBoard();

    

    boardManager.addNewSymbol(Cordinates(40, 1), PLAYER_SYMBOL);
    //boardManager.addNewSymbol(1,1, COMPUTER_SYMBOL);
    boardManager.printBoard();


    return 0;
}

 // TODO: zaimplementować singletona! klasach Manger