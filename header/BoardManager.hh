#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <iostream>
#include <vector>
#include "SymbolManager.hh"
#include "Cordinates.hh"

class BoardManager {
public:
    static BoardManager* getInstance();
    ~BoardManager();

    void resetEverySlotAndSetSize(const int NEW_BOARD_SIZE);
    void resetEverySlot();
    const bool addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& SYMBOL);

    
    void printBoard() const;
    const bool isAnyEmptySlot() const;
    const SymbolEnum findWinner(const int POINTS_FOR_VICTORY) const;
    std::vector<Cordinates> getEveryPossibleMove() const;

    void createBackUp();
    void retrieveBackUp();

private:
    static BoardManager* instance;
    BoardManager();

    SymbolManager* symbolManager = SymbolManager::getInstance();

    std::vector<std::vector<char>> board;
    int boardSize;
    int quantityOfTakenSlots;

    std::vector<std::vector<char>> BOARD_BACK_UP;
    int BOARD_SIZE_BACK_UP = -1;
    int QUANTITY_OF_TAKEN_SLOTS_BACK_UP = -1;

    const int DEFAULT_BOARD_SIZE = 3;

    const bool validateCordinates(const Cordinates& CORDINATES) const;
    const bool isSlotEmpty(const Cordinates& CORDINATES) const;

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
