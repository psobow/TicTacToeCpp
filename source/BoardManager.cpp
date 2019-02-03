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

void BoardManager::resetEverySlotAndSetSize(const unsigned int NEW_BOARD_SIZE){
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

bool BoardManager::addNewSymbol(const Cordinates& CORDINATES, const SymbolEnum& symbolEnum){
    bool isValid = validateCordinates(CORDINATES);
    if (isValid){
        char newSymbol = symbolManager.getCharFromEnum(symbolEnum); 
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
    if(board[CORDINATES.getRow()][CORDINATES.getColumn()] != symbolManager.getCharFromEnum(EMPTY_SLOT_SYMBOL)){
        return false;
    }
    return true;
}

const bool BoardManager::isAnyEmptySlot() const {
    return quantityOfTakenSlots < boardSize * boardSize;
}

const int BoardManager::getBoardSize() const {
    return boardSize;
}

bool BoardManager::isBoardInWinState(const unsigned int VICTORY_POINTS) const {

        // dla każdego slota na planszy wykonujemy:

            // 1.sprawdź czy możliwe jest dokonanie sprawdzenia o VICTORY_POINTS slotów na prawo
                // 2.sprawdź czy VICTORY_POINTS slotów na prawo zawiera znak różny od emptySymbol
                // 3.wykonaj sprawdzenie na prawo

                // sprawdź czy możliwe jest dokonanie sprawdzenia o VICTORY_POINTS slotów w dół
                    // wykonaj na prawo po skosie w dół
                    // wykonaj w dół


            // sprawdź czy możliwe dokonać sprawdzenia o vicotry points w dół oraz w lewo 
                // wykonaj sprawdzenie w lewo po skosie w dół



    const int LAST_VALID_INDEX = boardSize - 1;
    bool result;

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            // 1.
            if (col + VICTORY_POINTS <= LAST_VALID_INDEX ) {
                //2. zrobić z każdego kroku prywatne funkcje
                int howManyTakenSlots = 0;
                for(int i = 0; i < VICTORY_POINTS; i++){
                    if (isEmptySlot(Cordinates(col, i)) == false) {
                        howManyTakenSlots++;
                    }
                }
                // return howManyTakenSlots == VICTORY_POINTS
            }


        }
    }
    return false;
}
