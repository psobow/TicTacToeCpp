#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include "SymbolManager.hh"
#include "Cordinates.hh"

#include <iostream>
#include <vector>


class BoardManager {
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
    const int DEFAULT_BOARD_SIZE = 3;
    
    BoardManager(const BoardManager&) = delete;
    static BoardManager* instance;
    BoardManager();

    SymbolManager* symbolManager = SymbolManager::getInstance();

    std::vector<std::vector<char>> board;
    int boardSize;



    const bool validateCordinates(const Cordinates& CORDINATES) const;
    const bool isSlotEmpty(const Cordinates& CORDINATES) const;

    // TODO: zaimplementować algorytm z użyciem wielu wątków
    #pragma region findWinner algorithm 
    // EAST:
    const bool isPossibleToCheckEastSlots(const int COLUMN, const int POINTS_FOR_VICTORY) const;
    const bool areEastSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;
    const bool areEastSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;

    // SOUTH:
    const bool isPossibleToCheckSouthSlots(const int ROW, const int POINTS_FOR_VICTORY) const;
    const bool areSouthSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;
    const bool areSouthSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;

    // EAST-SOUTH
    const bool areEastSouthSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;
    const bool areEastSouthSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;

    // WEST-SOUTH:
    const bool isPossibleToCheckWestSlots(const int COLUMN, const int POINTS_FOR_VICTORY) const;
    const bool areWestSouthSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;
    const bool areWestSouthSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const;    
    #pragma endregion

};

#endif
