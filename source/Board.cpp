#include <iostream>
#include "../header/Board.hh"


Board::Board(){
    resetEveryValueAndSetSize(DEFAULT_BOARD_SIZE);
}

Board::~Board(){}


void Board::resetEveryValueAndSetSize(const int BOARD_SIZE){
    if (BOARD_SIZE < 3) {
        std::cout << "Board size need to be equal or greater than 3." << std::endl;
        return;
    }

    board_vec.clear();

    std::vector<char> row;
    for(int i = 0; i < BOARD_SIZE; i++){
        row.push_back('-');
    }
    for(int i = 0; i < BOARD_SIZE; i++){
        board_vec.push_back(row);
    }

    boardSize = BOARD_SIZE;
}

void Board::printBoard(){
    if (boardSize < 3) {
        return;
    }

    // print index on the top
    std::cout << "  "; 
    for (int i = 0; i < boardSize; i++) {
        std::cout << " " << i ;
    }
    std::cout << std::endl;

    // print top line 
    std::cout << " +";
    for (int i = 0; i < (2*boardSize) +1 ; i++){
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    // print middle of the board
    for (int row = 0; row < boardSize; row++){
        std::cout << row << "|";
        for (int col = 0; col < boardSize; col++){
            std::cout << " " << board_vec[row][col];
        }
        std::cout << " |" << std::endl;
    }

    // print bottom line 
    std::cout << " +";
    for (int i = 0; i < (2*boardSize) +1 ; i++){
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}

void Board::replaceChar(const int row, const int col, const char value){
    if (row >= boardSize || row < 0 || col >= boardSize || col < 0){
        std::cout << "Incorrect cordinates." << std::endl;
        return;
    }

    if(board_vec[row][col] != '-'){
        std::cout << "Slot already taken!" << std::endl;
        return;
    }

    board_vec[row][col] = value;
}

void Board::resetEveryValue(){
    resetEveryValueAndSetSize(boardSize);
}