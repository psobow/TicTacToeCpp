#include <iostream>
#include <vector>
#include "SymbolManager.hh"


class BoardManager {
private:
    SymbolManager symbolManager;
    const int DEFAULT_BOARD_SIZE = 3;
    std::vector<std::vector<char>> board_vec;
    int boardSize;

public:
    BoardManager();
    ~BoardManager();

    void resetEverySymbolAndSetSize(const int BOARD_SIZE);
    void resetEverySymbol();
    void printBoard();
    void addNewSymbol(const int row, const int col, SymbolEnum symbolEnum);
};
