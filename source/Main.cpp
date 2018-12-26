#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
using namespace std;



int main() 
{
    cout << "Hello, World!\n" << endl;

    GameManager game;
    game.printMenu();


    return 0;
}

 // TODO: zaimplementować singletona! tutaj oraz w innych klasach manger
 // TODO: zaimplementować obsługę błędów oraz wyrzucanie wyjątków, lub komnikatów za pomocą cerr