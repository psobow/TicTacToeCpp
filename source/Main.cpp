#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
#include "../header/Cordinates.hh"


int main() 
{
    std::cout << "Hello, World!\n" << std::endl;

    BoardManager boardManager = *BoardManager::getInstance();


    boardManager.addNewSymbol(Cordinates(0, 0), PLAYER);
    boardManager.addNewSymbol(Cordinates(0, 1), PLAYER);
    //boardManager.addNewSymbol(Cordinates(0, 2), PLAYER);

    boardManager.addNewSymbol(Cordinates(2, 0), PLAYER);
    boardManager.addNewSymbol(Cordinates(2, 1), PLAYER);
    boardManager.addNewSymbol(Cordinates(2, 2), PLAYER);


    boardManager.findWinner(3);

    boardManager.printBoard();


/* Testy konstruktora kopiującego klasy vector:

std::vector<int> testVector;
std::vector<int> secondVector;

testVector.push_back(1);

secondVector = testVector;

std::cout << "Rozmiar secondVector: " << secondVector.size() << "\n";

secondVector.push_back(2);

std::cout << "Rozmiar testVector: " << testVector.size() << "\n";
std::cout << "Rozmiar secondVector: " << secondVector.size() << "\n";
*/
    return 0;
}
