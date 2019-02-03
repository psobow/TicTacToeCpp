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

public:
    BoardManager();
    ~BoardManager();

    void resetEverySlotAndSetSize(const unsigned int NEW_BOARD_SIZE);
    void resetEverySlot();
    bool addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& symbolEnum);

    bool isBoardInWinState(const unsigned int VICTORY_POINTS) const;
    void printBoard() const;
    const bool isAnyEmptySlot() const;
    const int getBoardSize() const;
};

#endif
