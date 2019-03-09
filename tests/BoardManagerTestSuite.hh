#ifndef BOARD_MANAGER_TEST_H
#define BOARD_MANAGER_TEST_H

#include "../header/BoardManager.hh"

// this namespace should never be used outside tests
class BoardManagerTestSuite {
private:
    BoardManager *boardManager = BoardManager::getInstance();
public:
    BoardManagerTestSuite() {}

    // this interface allow to acces private methods from BoardManager in order to test them.
    const std::vector<std::vector<char>>& getBoard() const;

   
    // EAST:
    const bool executeIsPossibleToCheckEastSlots(       const Cordinates& CORDINATES) const;
    const bool executeAreEastSlotsNotEmpty(             const Cordinates& CORDINATES) const;
    const bool executeAreEastSlotsContainWinState(      const Cordinates& CORDINATES) const;

    // SOUTH:
    const bool executeIsPossibleToCheckSouthSlots(      const Cordinates& CORDINATES) const;
    const bool executeAreSouthSlotsNotEmpty(            const Cordinates& CORDINATES) const;
    const bool executeAreSouthSlotsContainWinState(     const Cordinates& CORDINATES) const;

    // EAST-SOUTH
    const bool executeAreEastSouthSlotsNotEmpty(        const Cordinates& CORDINATES) const;
    const bool executeAreEastSouthSlotsContainWinState( const Cordinates& CORDINATES) const;

    // WEST-SOUTH:
    const bool executeIsPossibleToCheckWestSlots(       const Cordinates& CORDINATES) const;
    const bool executeAreWestSouthSlotsNotEmpty(        const Cordinates& CORDINATES) const;
    const bool executeAreWestSouthSlotsContainWinState( const Cordinates& CORDINATES) const;  
    
};

#endif