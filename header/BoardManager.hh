#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include "SymbolManager.hh"
#include "Cordinates.hh"

#include <iostream>
#include <vector>

class BoardManagerTestSuite;

class BoardManager  {
    friend class BoardManagerTestSuite;
public:
    static BoardManager* getInstance();
    ~BoardManager();

    void printBoard() const;
    const SymbolEnum findWinner(const int POINTS_FOR_VICTORY) const;
    std::vector<Cordinates> getEveryEmptySlotCordinates() const;
    const int getQuantityOfTakenSlots() const;
    const bool isAnyEmptySlot() const;

    void resetEverySlotAndSetSize(const int NEW_BOARD_SIZE);
    void resetEverySlot();
    void resetSlot(const Cordinates& CORDINATES);
    const bool addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& SYMBOL);
    

private:   
    BoardManager(const BoardManager&) = delete;
    BoardManager& operator=(const BoardManager&) = delete;
    static BoardManager* instance;
    BoardManager();
    
    SymbolManager* symbolManager = SymbolManager::getInstance();

    const int DEFAULT_BOARD_SIZE = 3;
    std::vector<std::vector<char>> board;
    int boardSize;
    int quantityOfTakenSlots;

    const bool areValidCordinates(const Cordinates& CORDINATES) const;
    const bool isNotEmptySymbol(const SymbolEnum& SYMBOL) const;
    const bool isSlotEmpty(const Cordinates& CORDINATES) const;

    // TODO: zaimplementować algorytm z użyciem wielu wątków
    #pragma region findWinner algorithm 
    // EAST:
    const bool isPossibleToCheckEastSlots(      const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool areEastSlotsNotEmpty(            const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool areEastSlotsContainWinState(     const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;

    // SOUTH:
    const bool isPossibleToCheckSouthSlots(     const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool areSouthSlotsNotEmpty(           const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool areSouthSlotsContainWinState(    const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;

    // EAST-SOUTH
    const bool areEastSouthSlotsNotEmpty(       const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool areEastSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;

    // WEST-SOUTH:
    const bool isPossibleToCheckWestSlots(      const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool areWestSouthSlotsNotEmpty(       const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;
    const bool areWestSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const;    
    #pragma endregion
};

#endif
