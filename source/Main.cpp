#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
#include "../header/Cordinates.hh"
using namespace std;



int main() 
{
    cout << "Hello, World!\n" << endl;

    BoardManager boardManager = *BoardManager::getInstance();
    boardManager.createBackUp();

    boardManager.addNewSymbol(Cordinates(0, 0), PLAYER);

    boardManager.printBoard();

    std::cout<< " \n wgrywam back up...\n";

    boardManager.retrieveBackUp();


    boardManager.printBoard();

    boardManager.addNewSymbol(Cordinates(1, 1), PLAYER);

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
