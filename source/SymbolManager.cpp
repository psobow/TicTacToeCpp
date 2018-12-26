#include "../header/SymbolManager.hh"

SymbolManager::SymbolManager() {};
SymbolManager::~SymbolManager() {};

void SymbolManager::switchPlayerAndComputerSymbol() {
    char tempPlayerSymbol = playerSymbol;
    playerSymbol = computerSymbol;
    computerSymbol = tempPlayerSymbol;
}

const char SymbolManager::getSymbolFromEnum(SymbolEnum symbolEnum){

    char copySymbol = ' ';
    switch(symbolEnum) {
        case EMPTY_SLOT_SYMBOL: 
            copySymbol = emptySlotSymbol;
        break;
        case PLAYER_SYMBOL:
            copySymbol = playerSymbol;
        break;
        case COMPUTER_SYMBOL:
            copySymbol = computerSymbol;
        break;
        default:
        break;

    }
    return copySymbol;
}

const char SymbolManager::getEmptySlotSymbol(){
    return emptySlotSymbol;
}
