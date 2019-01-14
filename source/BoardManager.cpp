#include "../header/BoardManager.hh"


BoardManager::BoardManager(){
    resetEverySlotAndSetSize(DEFAULT_BOARD_SIZE);
}

BoardManager::~BoardManager(){}

void BoardManager::resetEverySlotAndSetSize(const int NEW_BOARD_SIZE){
    if (NEW_BOARD_SIZE < 3) {
        std::cerr << "Board size need to be equal or greater than 3. Could not set board size." << std::endl;
        return;
    }

    board_vec.clear();

    std::vector<char> row;
    for(int i = 0; i < NEW_BOARD_SIZE; i++){
        row.push_back(symbolManager.getEmptySlotSymbol());
    }
    for(int i = 0; i < NEW_BOARD_SIZE; i++){
        board_vec.push_back(row);
    }

    boardSize = NEW_BOARD_SIZE;
}

void BoardManager::resetEverySlot(){
    resetEverySlotAndSetSize(boardSize);
}

bool BoardManager::addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& symbolEnum){
    if( !CORDINATES.getAreCordinatesValid()) {
        std::cerr << "There was incorrect cordinates. Could not add new symbol.\n";
        return false;
    }

    bool isEmpty = isEmptySlot(CORDINATES);
    if (isEmpty){
        char newSymbol = symbolManager.getCharFromEnum(symbolEnum); 
        board_vec[CORDINATES.getRow()][CORDINATES.getColumn()] = newSymbol;
        return true;
    }
    std::cerr << "Slot was taken. Could not add new symbol\n";
    return false;
}

void BoardManager::printBoard() const {
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

const bool BoardManager::isEmptySlot(const Cordinates& CORDINATES) const {
    if(board_vec[CORDINATES.getRow()][CORDINATES.getColumn()] != symbolManager.getEmptySlotSymbol()){
        return false;
    }
    return true;
}

const bool BoardManager::isAnyEmptySlot() const {
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if (board_vec[i][j] == symbolManager.getEmptySlotSymbol()) {
                return true;
            }
        }
    }
    return false;
}

const int BoardManager::getBoardSize() const {
    return boardSize;
}
