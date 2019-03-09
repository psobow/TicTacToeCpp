#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <iostream>
#include <vector>

#include "Cordinates.hh"
#include "GameOptionsManager.hh"

class BoardManager { friend class BoardManagerTestSuite;
public:
    static BoardManager* getInstance();
    ~BoardManager() {};

    void resetEverySlotAndSetSize(const int NEW_BOARD_SIZE);
    void resetEverySlot();
    void resetSlot(const Cordinates& CORDINATES);
    const bool addNewCharacter(const Cordinates& CORDINATES, const Participant& PLAYER);

    void printBoard() const;
    const Participant findWinner() const;
    std::vector<Cordinates> getEveryEmptySlotCordinates() const;
    const int getQuantityOfTakenSlots() const;
    const bool isAnyEmptySlot() const;
    const bool isSlotEmpty(const Cordinates& CORDINATES) const;

private:
    std::vector<std::vector<char>> board;
    int quantityOfTakenSlots;
    
    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
    
    // Singleton
    static BoardManager *instance;
    BoardManager();
    BoardManager(const BoardManager&) = delete;
    BoardManager& operator=(const BoardManager&) = delete;


    // TODO: implement algorithm with multi threads.
    #pragma region findWinner algorithm
    // EAST:
    const bool isPossibleToCheckEastSlots(      const Cordinates& CORDINATES ) const;
    const bool areEastSlotsNotEmpty(            const Cordinates& CORDINATES ) const;
    const bool areEastSlotsContainWinState(     const Cordinates& CORDINATES ) const;

    // SOUTH:
    const bool isPossibleToCheckSouthSlots(     const Cordinates& CORDINATES ) const;
    const bool areSouthSlotsNotEmpty(           const Cordinates& CORDINATES ) const;
    const bool areSouthSlotsContainWinState(    const Cordinates& CORDINATES ) const;

    // EAST-SOUTH
    const bool areEastSouthSlotsNotEmpty(       const Cordinates& CORDINATES ) const;
    const bool areEastSouthSlotsContainWinState(const Cordinates& CORDINATES ) const;

    // WEST-SOUTH:
    const bool isPossibleToCheckWestSlots(      const Cordinates& CORDINATES ) const;
    const bool areWestSouthSlotsNotEmpty(       const Cordinates& CORDINATES ) const;
    const bool areWestSouthSlotsContainWinState(const Cordinates& CORDINATES ) const;
    #pragma endregion
};

#endif