#include "../header/BoardManager.hh"


BoardManager* BoardManager::instance = nullptr;

BoardManager* BoardManager::getInstance(){
    if(instance == nullptr) {
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
        std::cerr << "Board size need to be inteager from 3 to 9. Could not change board size.\n";
        return;
    }

    board.clear();
    boardSize = NEW_BOARD_SIZE;
    quantityOfTakenSlots = 0;

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

void BoardManager::resetSlot(const Cordinates& CORDINATES){
    bool validation = (areValidCordinates(CORDINATES) && ( ! isSlotEmpty(CORDINATES)) );
    if(validation){
        board[CORDINATES.getRow()][CORDINATES.getColumn()] = symbolManager->getCharFromEnum(NONE);
        quantityOfTakenSlots--;
    }
}

const bool BoardManager::addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& SYMBOL){
    bool isValid = ( areValidCordinates(CORDINATES) && isNotEmptySymbol(SYMBOL) && isSlotEmpty(CORDINATES) );
    if (isValid){
        char newSymbol = symbolManager->getCharFromEnum(SYMBOL); 
        board[CORDINATES.getRow()][CORDINATES.getColumn()] = newSymbol;
        quantityOfTakenSlots++;
        return true;
    }
    return false;
}

const bool BoardManager::areValidCordinates(const Cordinates& CORDINATES) const {
    const int row = CORDINATES.getRow();
    const int col = CORDINATES.getColumn();

    if (row >= boardSize || row < 0 ||
        col >= boardSize || col < 0){
        return false;
    } else {
        return true;
    }
}

const bool BoardManager::isNotEmptySymbol(const SymbolEnum& SYMBOL) const{
    return SYMBOL != NONE;
}

const bool BoardManager::isSlotEmpty(const Cordinates& CORDINATES) const {
    return ( board[CORDINATES.getRow()][CORDINATES.getColumn()] == symbolManager->getCharFromEnum(NONE) );
}


const bool BoardManager::isAnyEmptySlot() const {
    return quantityOfTakenSlots < boardSize*boardSize;
}

const int BoardManager::getQuantityOfTakenSlots() const {
    return quantityOfTakenSlots;
}

std::vector<Cordinates> BoardManager::getEveryEmptySlotCordinates() const {
    std::vector<Cordinates> emptySlots;

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            if( isSlotEmpty(Cordinates(row, col)) ){
                emptySlots.push_back(Cordinates(row, col));
            }
        }
    }
    return emptySlots;
}


#pragma region findWinner algorithm 

const SymbolEnum BoardManager::findWinner(const int POINTS_FOR_VICTORY) const {
    if( getQuantityOfTakenSlots() < (2 * POINTS_FOR_VICTORY)-1 ) return NONE; // there is no winner with this amount of taken slots.

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            Cordinates currentSlot(row,col);

            if(isSlotEmpty(currentSlot) == false){ // If current slot is empty, skip that.
            
                //EAST:
                bool eastResult = isPossibleToCheckEastSlots(currentSlot, POINTS_FOR_VICTORY);
                if (eastResult) { 
                    if(areEastSlotsNotEmpty(currentSlot, POINTS_FOR_VICTORY)) {
                        if(areEastSlotsContainWinState(currentSlot, POINTS_FOR_VICTORY)){
                            return symbolManager->getEnumFromChar(board[row][col]);
                        }
                    }
                }

                //SOUTH:
                bool southResult = isPossibleToCheckSouthSlots(currentSlot, POINTS_FOR_VICTORY);
                if(southResult){
                    if(areSouthSlotsNotEmpty(currentSlot, POINTS_FOR_VICTORY)){
                        if(areSouthSlotsContainWinState(currentSlot, POINTS_FOR_VICTORY)) {
                            return symbolManager->getEnumFromChar(board[row][col]);
                        }
                    }
                }

                //EAST-SOUTH:
                if(eastResult && southResult) {
                    if(areEastSouthSlotsNotEmpty(currentSlot, POINTS_FOR_VICTORY)) {
                        if(areEastSouthSlotsContainWinState(currentSlot, POINTS_FOR_VICTORY)){
                            return symbolManager->getEnumFromChar(board[row][col]);
                        }
                    }
                }

                //WEST-SOUTH:
                bool westResult = isPossibleToCheckWestSlots(currentSlot, POINTS_FOR_VICTORY);
                if(westResult && southResult){
                    if(areWestSouthSlotsNotEmpty(currentSlot, POINTS_FOR_VICTORY)){
                        if(areWestSouthSlotsContainWinState(currentSlot, POINTS_FOR_VICTORY)){
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

const bool BoardManager::isPossibleToCheckEastSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    return (CORDINATES.getColumn() + POINTS_FOR_VICTORY) <= boardSize;
}

const bool BoardManager::areEastSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
    for(int col = 1; col < POINTS_FOR_VICTORY; col++){
        if (isSlotEmpty(Cordinates(ROW, COLUMN+col)) == true) {
            return false;
        }
    }
    return true;
}

const bool BoardManager::areEastSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
    int howManyEqualPairs = 0;
    for(int col = 1; col < POINTS_FOR_VICTORY; col++){
        if(board[ROW][COLUMN] == board[ROW][COLUMN+col] ){
            howManyEqualPairs++;
        }
    }
    return howManyEqualPairs == (POINTS_FOR_VICTORY - 1);
}

// SOUTH:

const bool BoardManager::isPossibleToCheckSouthSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    return (CORDINATES.getRow() + POINTS_FOR_VICTORY) <= boardSize;
}

const bool BoardManager::areSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
    for(int row = 1; row < POINTS_FOR_VICTORY; row++){
        if(isSlotEmpty(Cordinates(ROW+row, COLUMN)) == true){
            return false;
        }
    }
    return true;
}

const bool BoardManager::areSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
    int howManyEqualPairs = 0;
    for(int row = 1; row < POINTS_FOR_VICTORY; row++){
        if(board[ROW][COLUMN] == board[ROW+row][COLUMN] ){
            howManyEqualPairs++;
        }
    }
    return howManyEqualPairs == (POINTS_FOR_VICTORY - 1);
}

// EAST-SOUTH:

const bool BoardManager::areEastSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
    for(int i = 1; i < POINTS_FOR_VICTORY; i++){
        if(isSlotEmpty(Cordinates(ROW+i, COLUMN+i)) == true){
            return false;
        }
    }
    return true;
}

const bool BoardManager::areEastSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
    int howManyEqualPairs = 0;
    for(int i = 1; i < POINTS_FOR_VICTORY; i++) {
        if(board[ROW][COLUMN] == board[ROW+i][COLUMN+i]){
            howManyEqualPairs++;
        }
    }
    return howManyEqualPairs == (POINTS_FOR_VICTORY - 1);
}

// WEST-SOUTH:

const bool BoardManager::isPossibleToCheckWestSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    return ((CORDINATES.getColumn()-POINTS_FOR_VICTORY) >= -1) && (CORDINATES.getColumn() < boardSize);
}

const bool BoardManager::areWestSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
    for(int i = 1; i < POINTS_FOR_VICTORY; i++){
        if(isSlotEmpty(Cordinates(ROW+i, COLUMN-i)) == true){
            return false;
        }
    }
    return true;
}

const bool BoardManager::areWestSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    const int ROW = CORDINATES.getRow();
    const int COLUMN = CORDINATES.getColumn();
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
