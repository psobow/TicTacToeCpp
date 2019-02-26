#ifndef MINMAX_MANAGER_H
#define MINMAX_MANAGER_H

#include <iostream>

#include "Cordinates.hh"
#include "BoardManager.hh"
#include "GameManager.hh"

class MinMaxManager {
public:
    static MinMaxManager* getInstance();
    ~MinMaxManager() {};
    

    // TODO: change this function name
    void mainMinMax();

    

private:
    MinMaxManager(const MinMaxManager&) = delete;
    MinMaxManager& operator=(const MinMaxManager&) = delete;
    static MinMaxManager* instance;
    MinMaxManager() : computerChoice(0,0) {}

    SymbolManager *symbolManager = SymbolManager::getInstance();
    BoardManager *boardManager = BoardManager::getInstance();
    GameManager *gameManager = GameManager::getInstance();

    const int HIGHEST_SCORE = 1000;
    
    // wykorzystanie tego pola nie jest dobry pomysłem przy algorytmie wielowątkowym. trzeba będzie to synchronizować
    Cordinates computerChoice;



    const int scoreGameFromComputerPOV(const int depth) const; // POV = Point of view

    //TODO: change this function name
    int makeNextMove(const SymbolEnum& turnTakingPlayer, int depth);

    int getMaxValueIndex(const std::vector<int>& vec) const;
    int getMinValueIndex(const std::vector<int>& vec) const;
};


#endif