#ifndef MINMAX_MANAGER_H
#define MINMAX_MANAGER_H

#include <stdexcept>

#include "BoardManager.hh"
#include "Cordinates.hh"
#include "GameOptionsManager.hh"


class MinMaxManager { friend class MinMaxManagerTestSuite;
public:
    static MinMaxManager* getInstance();
    ~MinMaxManager() {};
    
    const bool executeTheBestComputerMove();

private:
    const int HIGHEST_SCORE = 1000;
    Cordinates theBestMoveCordinates; //trzeba będzie to synchronizować na wielu wątkach 

    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
    BoardManager *boardManager = BoardManager::getInstance();
    
    // Singleton
    static MinMaxManager *instance;
    MinMaxManager() : theBestMoveCordinates(0,0) {}
    MinMaxManager(const MinMaxManager&) = delete;
    MinMaxManager& operator=(const MinMaxManager&) = delete;

    const int calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int depth);

    const int scoreGameFromComputerPOV(const int DEPTH) const; // POV = Point of view
    const int getMaxValueIndex(const std::vector<int>& VEC) const;
    const int getMinValueIndex(const std::vector<int>& VEC) const;
};

#endif