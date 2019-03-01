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
    const int scoreGameFromComputerPOV(const int depth) const; // POV = Point of view
    const int getMaxValueIndex(const std::vector<int>& vec) const;
    const int getMinValueIndex(const std::vector<int>& vec) const;
    const Cordinates& getTheBestMove() const;

    const int calculateTheBestMove(const SymbolEnum& turnTakingPlayer, int depth);
    
    
};




#endif