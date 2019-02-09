#include "../header/BoardManager.hh"


BoardManager* BoardManager::instance = 0;

BoardManager* BoardManager::getInstance(){
    if(instance == 0) {
        instance = new BoardManager();
    }
    return instance;
}

BoardManager::BoardManager(){
    resetEverySlotAndSetSize(DEFAULT_BOARD_SIZE);
}
BoardManager::~BoardManager(){}

void BoardManager::resetEverySlotAndSetSize(const int NEW_BOARD_SIZE){
    if (NEW_BOARD_SIZE < 3 || NEW_BOARD_SIZE > 9) {
        std::cerr << "Board size need to be inteager from 3 to 9. Could not change board size." << std::endl;
        return;
    }

    board.clear();
    quantityOfTakenSlots = 0;
    boardSize = NEW_BOARD_SIZE;

    std::vector<char> row;
    for(int i = 0; i < NEW_BOARD_SIZE; i++){
        row.push_back(symbolManager->getCharFromEnum(NONE));
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
        char newSymbol = symbolManager->getCharFromEnum(SYMBOL); 
        board[CORDINATES.getRow()][CORDINATES.getColumn()] = newSymbol;
        quantityOfTakenSlots++;
        return true;
    }
    std::cerr << "Could not add new symbol. There was invalid cordinates or taken slot.\n";
    return false;
}

const bool BoardManager::validateCordinates(const Cordinates& CORDINATES) const {
    const int row = CORDINATES.getRow();
    const int col = CORDINATES.getColumn();

    if (row >= boardSize || row < 0 ||
        col >= boardSize || col < 0){
        return false;
        }
    
    return isSlotEmpty(CORDINATES);
}

const bool BoardManager::isSlotEmpty(const Cordinates& CORDINATES) const {
    return board[CORDINATES.getRow()][CORDINATES.getColumn()] == symbolManager->getCharFromEnum(NONE);
}

const bool BoardManager::isAnyEmptySlot() const {
    return quantityOfTakenSlots < boardSize * boardSize;
}

std::vector<Cordinates> BoardManager::getEveryPossibleMove() const{
    std::vector<Cordinates> possibleMoves;
    if(isAnyEmptySlot() == false) return possibleMoves;
    
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            if(isSlotEmpty(Cordinates(row, col))){
                possibleMoves.push_back(Cordinates(row, col));
            }
        }
    }
    return possibleMoves;
}

void BoardManager::createBackUp(){
    BOARD_BACK_UP = board;
    BOARD_SIZE_BACK_UP = boardSize;
    QUANTITY_OF_TAKEN_SLOTS_BACK_UP = quantityOfTakenSlots;
}

void BoardManager::retrieveBackUp(){
    if(BOARD_SIZE_BACK_UP == -1 || QUANTITY_OF_TAKEN_SLOTS_BACK_UP == -1) {
        std::cerr << "There is no back up to retrieve. Create back up first.";
        return;
    }

    board = BOARD_BACK_UP;
    boardSize = BOARD_SIZE_BACK_UP;
    quantityOfTakenSlots = QUANTITY_OF_TAKEN_SLOTS_BACK_UP;
}

#pragma region findWinner algorithm 

const SymbolEnum BoardManager::findWinner(const int POINTS_FOR_VICTORY) const {
    if(quantityOfTakenSlots < 2*boardSize) return NONE;

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){

            if(isSlotEmpty(Cordinates(row,col)) == false){ // If current slot is empty, skip that.
            
                //EAST:
                bool eastResult = isPossibleToCheckEastSlots(col, POINTS_FOR_VICTORY);
                if (eastResult) { 
                    if(areEastSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)) {
                        if(areEastSlotsContainWinState(row, col, POINTS_FOR_VICTORY)){
                            return symbolManager->getEnumFromChar(board[row][col]);
                        }
                    }
                }

                //SOUTH:
                bool southResult = isPossibleToCheckSouthSlots(row, POINTS_FOR_VICTORY);
                if(southResult){
                    if(areSouthSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)){
                        if(areSouthSlotsContainWinState(row, col, POINTS_FOR_VICTORY)) {
                            return symbolManager->getEnumFromChar(board[row][col]);
                        }
                    }
                }

                //EAST-SOUTH:
                if(eastResult && southResult) {
                    if(areEastSouthSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)) {
                        if(areEastSouthSlotsContainWinState(row, col, POINTS_FOR_VICTORY)){
                            return symbolManager->getEnumFromChar(board[row][col]);
                        }
                    }
                }

                //WEST-SOUTH:
                bool westResult = isPossibleToCheckWestSlots(col, POINTS_FOR_VICTORY);
                if(westResult && southResult){
                    if(areWestSouthSlotsNotEmpty(row, col, POINTS_FOR_VICTORY)){
                        if(areWestSouthSlotsContainWinState(row, col, POINTS_FOR_VICTORY)){
                            return symbolManager->getEnumFromChar(board[row][col]);
                        }
                    }
                }
                

            }
        }
    }
    return NONE;
}

// EAST:

const bool BoardManager::isPossibleToCheckEastSlots(const int COLUMN, const int POINTS_FOR_VICTORY) const {
    return (COLUMN + POINTS_FOR_VICTORY) <= boardSize;
}

const bool BoardManager::areEastSlotsNotEmpty(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const {
    int howManyTakenSlots = 0;
    for(int col = 1; col < POINTS_FOR_VICTORY; col++){
        if (isSlotEmpty(Cordinates(ROW, COLUMN+col)) == false) {
            howManyTakenSlots++;
        }
    }
    return howManyTakenSlots == (POINTS_FOR_VICTORY - 1);
}

const bool BoardManager::areEastSlotsContainWinState(const int ROW, const int COLUMN, const int POINTS_FOR_VICTORY) const {
    int howManyEqualPairs = 0;
    for(int col = 1; col < POINTS_FOR_VICTORY; col++){
        if(board[ROW][COLUMN] == board[ROW][COLUMN+col] ){
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
        if(isSlotEmpty(Cordinates(ROW+row, COLUMN)) == false){
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
        if(isSlotEmpty(Cordinates(ROW+i, COLUMN+i)) == false){
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
        if(isSlotEmpty(Cordinates(ROW+i, COLUMN-i)) == false){
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
#pragma endregion

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