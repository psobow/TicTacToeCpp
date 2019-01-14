#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include <iostream>
#include <vector>
#include "SymbolManager.hh"
#include "Cordinates.hh"

class Cordinates;

class BoardManager {
private:
    const SymbolManager symbolManager;
    const int DEFAULT_BOARD_SIZE = 3;

    std::vector<std::vector<char>> board_vec;
    int boardSize;

public:
    BoardManager();
    ~BoardManager();

    void resetEverySlotAndSetSize(const int BOARD_SIZE);
    void resetEverySlot();
    bool addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& symbolEnum);

    void printBoard() const;
    const bool isEmptySlot(const Cordinates& CORDINATES) const;
    const bool isAnyEmptySlot() const;
    const int getBoardSize() const;
};

#endif
