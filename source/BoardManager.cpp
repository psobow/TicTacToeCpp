
#include "../header/BoardManager.hh"

using std::cout;
using std::endl;

BoardManager::BoardManager(){
    resetEverySymbolAndSetSize(DEFAULT_BOARD_SIZE);
}

BoardManager::~BoardManager(){}


void BoardManager::resetEverySymbolAndSetSize(const int BOARD_SIZE){
    if (BOARD_SIZE < 3) {
        cout << "Board size need to be equal or greater than 3." << endl;
        return;
    }

    board_vec.clear();

    std::vector<char> row;
    for(int i = 0; i < BOARD_SIZE; i++){
        row.push_back(symbolManager.getEmptySlotSymbol());
    }
    for(int i = 0; i < BOARD_SIZE; i++){
        board_vec.push_back(row);
    }

    boardSize = BOARD_SIZE;
}

void BoardManager::printBoard(){
    if (boardSize < 3) {
        return;
    }

    // print index on the top
    cout << "  "; 
    for (int i = 0; i < boardSize; i++) {
        cout << " " << i ;
    }
    cout << endl;

    // print top line 
    cout << " +";
    for (int i = 0; i < (2*boardSize) +1 ; i++){
        cout << "-";
    }
    cout << "+" << endl;

    // print middle of the board
    for (int row = 0; row < boardSize; row++){
        cout << row << "|";
        for (int col = 0; col < boardSize; col++){
            cout << " " << board_vec[row][col];
        }
        cout << " |" << endl;
    }

    // print bottom line 
    cout << " +";
    for (int i = 0; i < (2*boardSize) +1 ; i++){
        cout << "-";
    }
    cout << "+" << endl;
}

void BoardManager::addNewSymbol(const int row, const int col, SymbolEnum symbolEnum){
    if (row >= boardSize || row < 0 || col >= boardSize || col < 0){
        cout << "Incorrect cordinates." << endl;
        return;
    }

    if(board_vec[row][col] != symbolManager.getEmptySlotSymbol()){
        cout << "Slot already taken!" << endl;
        return;
    }
    char newSymbol = symbolManager.getSymbolFromEnum(symbolEnum); 

    board_vec[row][col] = newSymbol;
}

void BoardManager::resetEverySymbol(){
    resetEverySymbolAndSetSize(boardSize);
}