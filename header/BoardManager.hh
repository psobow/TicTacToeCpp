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

    const SymbolEnum isBoardInWinState(const int POINTS_FOR_VICTORY) const;
    void printBoard() const;
    const bool isAnyEmptySlot() const;
    const int getBoardSize() const;
    const auto& getBoard() const; // TODO: jeszcze nei wiem czy to będzie wgl potrzebne do czegos

    // TODO: być może trzeba będzie udostępnić możliwość kopiowanie vectora z boardem dla min maxa
private:
    static BoardManager* instance;
    BoardManager();

    SymbolManager* symbolManager = SymbolManager::getInstance();
    const int DEFAULT_BOARD_SIZE = 3;

    std::vector<std::vector<char>> board;
    int boardSize;
    int quantityOfTakenSlots;

    const bool isSlotEmpty(const Cordinates& CORDINATES) const;
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
};

#endif
