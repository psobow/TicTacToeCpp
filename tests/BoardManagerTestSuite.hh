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
    const bool executeIsPossibleToCheckEastSlots(       const Coordinates& COORDINATES) const;
    const bool executeAreEastSlotsNotEmpty(             const Coordinates& COORDINATES) const;
    const bool executeAreEastSlotsContainWinState(      const Coordinates& COORDINATES) const;

    // SOUTH:
    const bool executeIsPossibleToCheckSouthSlots(      const Coordinates& COORDINATES) const;
    const bool executeAreSouthSlotsNotEmpty(            const Coordinates& COORDINATES) const;
    const bool executeAreSouthSlotsContainWinState(     const Coordinates& COORDINATES) const;

    // EAST-SOUTH
    const bool executeAreEastSouthSlotsNotEmpty(        const Coordinates& COORDINATES) const;
    const bool executeAreEastSouthSlotsContainWinState( const Coordinates& COORDINATES) const;

    // WEST-SOUTH:
    const bool executeIsPossibleToCheckWestSlots(       const Coordinates& COORDINATES) const;
    const bool executeAreWestSouthSlotsNotEmpty(        const Coordinates& COORDINATES) const;
    const bool executeAreWestSouthSlotsContainWinState( const Coordinates& COORDINATES) const;  
    
};

#endif