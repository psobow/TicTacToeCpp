#ifndef MINMAX_MANAGER_H
#define MINMAX_MANAGER_H

#include <iostream>

#include "Cordinates.hh"
#include "BoardManager.hh"
#include "GameManager.hh"

class MinMaxManager {
public:
    static MinMaxManager* getInstance();
    ~MinMaxManager();
    const int scoreGameFromComputerPOV(const int depth) const;


    void mainMinMax();

    int getMaxValueIndex(const std::vector<int>& vec) const;
    int getMinValueIndex(const std::vector<int>& vec) const;

private:
    MinMaxManager(const MinMaxManager&) = delete;
    static MinMaxManager* instance;
    MinMaxManager();
    const int HIGHEST_SCORE = 1000;

    SymbolManager *symbolManager = SymbolManager::getInstance();
    BoardManager *boardManager = BoardManager::getInstance();
    GameManager *gameManager = GameManager::getInstance();

    // wykorzystanie tego pola nie jest dobry pomysłem przy algorytmie wielowątkowym.
    Cordinates computerChoice = Cordinates(0, 0);


    int makeNextMove(const SymbolEnum& turnTakingPlayer, int depth);

};

/*
    1. getEveryPosibleMove
  

*/


#endif