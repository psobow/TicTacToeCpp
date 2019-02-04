#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <iostream>
#include <vector>
#include "SymbolManager.hh"
#include "Cordinates.hh"

class BoardManager {
private:
    SymbolManager symbolManager;
    const int DEFAULT_BOARD_SIZE = 3;

    std::vector<std::vector<char>> board;
    int boardSize;
    int quantityOfTakenSlots;

    const bool isEmptySlot(const Cordinates& CORDINATES) const;
    const bool validateCordinates(const Cordinates& CORDINATES) const;

    // isBoardInWinState algorithm

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

public:
    BoardManager();
    ~BoardManager();

    void resetEverySlotAndSetSize(const int NEW_BOARD_SIZE);
    void resetEverySlot();
    const bool addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& SYMBOL);

    const bool isBoardInWinState(const int POINTS_FOR_VICTORY) const;
    void printBoard() const;
    const bool isAnyEmptySlot() const;
    const int getBoardSize() const;
};

#endif
