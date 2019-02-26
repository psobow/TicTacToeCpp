#ifndef BOARD_MANAGER_TEST_H
#define BOARD_MANAGER_TEST_H

#include <stdexcept>
#include <string>
#include "../header/BoardManager.hh"

// this namespace should never be used outside tests


class BoardManagerTestSuite {
private:
    BoardManager *boardManager = BoardManager::getInstance();
public:
    BoardManagerTestSuite();

    // this interface allow to acces private methods from BoardManager in order to test them.
    std::vector<std::vector<char>>& getBoard() const;

    const bool executeAreValidCordinates(const Cordinates& CORDINATES) const;
    const bool executeIsNotEmptySymbol(const SymbolEnum& SYMBOL) const;
    const bool executeIsSlotEmpty(const Cordinates& CORDINATES) const;

   
    // EAST:
    const bool executeIsPossibleToCheckEastSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool executeAreEastSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool executeAreEastSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;

    // SOUTH:
    const bool executeIsPossibleToCheckSouthSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool executeAreSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool executeAreSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;

    // EAST-SOUTH
    const bool executeAreEastSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool executeAreEastSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;

    // WEST-SOUTH:
    const bool executeIsPossibleToCheckWestSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool executeAreWestSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool executeAreWestSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;  
    
};



#endif