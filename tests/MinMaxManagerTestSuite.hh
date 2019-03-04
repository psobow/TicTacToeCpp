#ifndef MINMAX_MANAGER_TEST_H
#define MINMAX_MANAGER_TEST_H

#include "../header/MinMaxManager.hh"
#include <vector>

// this namespace should never be used outside tests

class MinMaxManagerTestSuite{
private:
    MinMaxManager *minMaxManager = MinMaxManager::getInstance();

public:
    MinMaxManagerTestSuite() {}

    // this interface allow to acces private methods from BoardManager in order to test them.
    const int scoreGameFromComputerPOV(const int DEPTH) const; // POV = Point of view
    const int getMaxValueIndex(const std::vector<int>& VEC) const;
    const int getMinValueIndex(const std::vector<int>& VEC) const;
    const Cordinates& getTheBestMove() const;

    const int calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int depth);
    
    
};




#endif