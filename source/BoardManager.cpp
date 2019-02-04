#include "../header/BoardManager.hh"


BoardManager::BoardManager(){
    resetEverySlotAndSetSize(DEFAULT_BOARD_SIZE);
}

BoardManager::~BoardManager(){}

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
            std::cout << " " << board[row][col];
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

void BoardManager::resetEverySlotAndSetSize(const int NEW_BOARD_SIZE){
    if (NEW_BOARD_SIZE < 3) {
        std::cerr << "Board size need to be equal or greater than 3. Could not change board size." << std::endl;
        return;
    }

    board.clear();
    quantityOfTakenSlots = 0;
    boardSize = NEW_BOARD_SIZE;

    std::vector<char> row;
    for(int i = 0; i < NEW_BOARD_SIZE; i++){
        row.push_back(symbolManager.getCharFromEnum(EMPTY_SLOT_SYMBOL));
    }
    for(int i = 0; i < NEW_BOARD_SIZE; i++){
        board.push_back(row);
    }    
}

void BoardManager::resetEverySlot(){
    resetEverySlotAndSetSize(boardSize);
}

const bool BoardManager::addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& SYMBOL){
    bool isValid = validateCordinates(CORDINATES);
    if (isValid){
        char newSymbol = symbolManager.getCharFromEnum(SYMBOL); 
        board[CORDINATES.getRow()][CORDINATES.getColumn()] = newSymbol;
        quantityOfTakenSlots++;
        return true;
    }
    std::cerr << "Could not add new symbol. There was invalid cordinates.\n";
    return false;
}

const bool BoardManager::validateCordinates(const Cordinates& CORDINATES) const {
    const int row = CORDINATES.getRow();
    const int col = CORDINATES.getColumn();

    if (row >= boardSize || row < 0 ||
        col >= boardSize || col < 0){
        return false;
        }
    
    return isEmptySlot(CORDINATES);
}

const bool BoardManager::isEmptySlot(const Cordinates& CORDINATES) const {
    return board[CORDINATES.getRow()][CORDINATES.getColumn()] == symbolManager.getCharFromEnum(EMPTY_SLOT_SYMBOL);
}

const bool BoardManager::isAnyEmptySlot() const {
    return quantityOfTakenSlots < boardSize * boardSize;
}

const int BoardManager::getBoardSize() const {
    return boardSize;
}


const bool BoardManager::isBoardInWinState(const int POINTS_FOR_VICTORY) const {
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){

            if(isEmptySlot(Cordinates(row,col)) == false){ // If current slot is empty, skip that.
            
                //EAST:
                bool eastResult = isPossibleToCheckEastSlots(col, POINTS_FOR_VICTORY);
                if (eastResult) { 
                    if(areEastSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)) {
                        if(areEastSlotsContainWinState(row, col, POINTS_FOR_VICTORY)){
                            return true;
                        }
                    }
                }

                //SOUTH:
                bool southResult = isPossibleToCheckSouthSlots(row, POINTS_FOR_VICTORY);
                if(southResult){
                    if(areSouthSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)){
                        if(areSouthSlotsContainWinState(row, col, POINTS_FOR_VICTORY)) {
                            return true;
                        }
                    }
                }

                //EAST-SOUTH:
                if(eastResult && southResult) {
                    if(areEastSouthSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)) {
                        if(areEastSouthSlotsContainWinState(row, col, POINTS_FOR_VICTORY)){
                            return true;
                        }
                    }
                }

                //WEST-SOUTH:
                bool westResult = isPossibleToCheckWestSlots(col, POINTS_FOR_VICTORY);
                if(westResult && southResult){
                    if(areWestSouthSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)){
                        if(areWestSouthSlotsContainWinState(row, col, POINTS_FOR_VICTORY)){
                            return true;
                        }
                    }
                }
                

            }

        }
    }
    return false;
}


// EAST:

const bool BoardManager::isPossibleToCheckEastSlots(const int COLUMN, const int POINTS_FOR_VICTORY) const {
    return (COLUMN + POINTS_FOR_VICTORY) <= boardSize;
}

const bool BoardManager::areEastSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const {
    int howManyTakenSlots = 0;
    for(int col = 1; col < POINTS_FOR_VICTORY; col++){
        if (isEmptySlot(Cordinates(ROW, COLUMN+col)) == false) {
            howManyTakenSlots++;
        }
    }
    return howManyTakenSlots == (POINTS_FOR_VICTORY - 1);
}

const bool BoardManager::areEastSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const {
    int howManyEqualPairs = 0;
    for(int col = 1; col < POINTS_FOR_VICTORY; col++){
        if( board[ROW][COLUMN] == board[ROW][COLUMN+col] ){
            howManyEqualPairs++;
        }
    }
    return howManyEqualPairs == (POINTS_FOR_VICTORY - 1);
}


// SOUTH:

const bool BoardManager::isPossibleToCheckSouthSlots(const int ROW, const int POINTS_FOR_VICTORY) const {
    return (ROW + POINTS_FOR_VICTORY) <= boardSize;
}

const bool BoardManager::areSouthSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const {
    int howManyTakenSlots = 0;
    for(int row = 1; row < POINTS_FOR_VICTORY; row++){
        if(isEmptySlot(Cordinates(ROW+row, COLUMN)) == false){
            howManyTakenSlots++;
        }
    }
    return howManyTakenSlots == (POINTS_FOR_VICTORY - 1);
}

const bool BoardManager::areSouthSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const {
    int howManyEqualPairs = 0;
    for(int row = 1; row < POINTS_FOR_VICTORY; row++){
        if(board[ROW][COLUMN] == board[ROW+row][COLUMN] ){
            howManyEqualPairs++;
        }
    }
    return howManyEqualPairs == (POINTS_FOR_VICTORY - 1);
}

// EAST-SOUTH:

const bool BoardManager::areEastSouthSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const{
    int howManyTakenSlots = 0;
    for(int i = 1; i < POINTS_FOR_VICTORY; i++){
        if(isEmptySlot(Cordinates(ROW+i, COLUMN+i)) == false){
            howManyTakenSlots++;
        }
    }
    return howManyTakenSlots == (POINTS_FOR_VICTORY - 1);
}
const bool BoardManager::areEastSouthSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const{
    int howManyEqualPairs = 0;
    for(int i = 1; i < POINTS_FOR_VICTORY; i++) {
        if(board[ROW][COLUMN] == board[ROW+i][COLUMN+i]){
            howManyEqualPairs++;
        }
    }
    return howManyEqualPairs == (POINTS_FOR_VICTORY - 1);
}


// WEST-SOUTH:

const bool BoardManager::isPossibleToCheckWestSlots(const int COLUMN, const int POINTS_FOR_VICTORY) const {
    return COLUMN - POINTS_FOR_VICTORY >= -1;
}

const bool BoardManager::areWestSouthSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const{
    int howManyTakenSlots = 0;
    for(int i = 1; i < POINTS_FOR_VICTORY; i++){
        if(isEmptySlot(Cordinates(ROW+i, COLUMN-i)) == false){
            howManyTakenSlots++;
        }
    }
    return howManyTakenSlots == (POINTS_FOR_VICTORY - 1);
}


const bool BoardManager::areWestSouthSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const{
    int howManyEqualPairs = 0;
    for(int i = 1; i < POINTS_FOR_VICTORY; i++) {
        if(board[ROW][COLUMN] == board[ROW+i][COLUMN-i]){
            howManyEqualPairs++;
        }
    }
    return howManyEqualPairs == (POINTS_FOR_VICTORY - 1);
}