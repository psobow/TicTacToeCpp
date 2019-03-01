#ifndef MINMAX_MANAGER_H
#define MINMAX_MANAGER_H

#include <iostream>
#include <stdexcept>

#include "Cordinates.hh"
#include "BoardManager.hh"
#include "GameManager.hh"

class MinMaxManagerTestSuite;

class MinMaxManager {
    friend class MinMaxManagerTestSuite;
public:
    static MinMaxManager* getInstance();
    ~MinMaxManager() {};
    
    void executeTheBestComputerMove();

private:
    MinMaxManager(const MinMaxManager&) = delete;
    MinMaxManager& operator=(const MinMaxManager&) = delete;
    static MinMaxManager *instance;
    MinMaxManager() : theBestMoveCordinates(0,0) {}

    SymbolManager *symbolManager = SymbolManager::getInstance();
    BoardManager *boardManager = BoardManager::getInstance();
    GameManager *gameManager = GameManager::getInstance();

    const int HIGHEST_SCORE = 1000;
    
    //trzeba będzie to synchronizować na wielu wątkach
    Cordinates theBestMoveCordinates;

    const int calculateTheBestMove(const SymbolEnum& turnTakingPlayer, int depth);
    const int scoreGameFromComputerPOV(const int depth) const; // POV = Point of view
    const int getMaxValueIndex(const std::vector<int>& vec) const;
    const int getMinValueIndex(const std::vector<int>& vec) const;
};

#endif