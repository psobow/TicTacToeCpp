#include "../header/SymbolManager.hh"

SymbolManager::SymbolManager() {};
SymbolManager::~SymbolManager() {};

void SymbolManager::switchPlayerAndComputerSymbol() {
    char tempPlayerSymbol = playerSymbol;
    playerSymbol = computerSymbol;
    computerSymbol = tempPlayerSymbol;
}

const char SymbolManager::getCharFromEnum(SymbolEnum symbolEnum) const {

    char result = ' ';
    switch(symbolEnum) {
        case EMPTY_SLOT_SYMBOL: 
            result = emptySlotSymbol;
        break;
        case PLAYER_SYMBOL:
            result = playerSymbol;
        break;
        case COMPUTER_SYMBOL:
            result = computerSymbol;
        break;
        default:
        break;

    }
    return result;
}

const char SymbolManager::getEmptySlotSymbol() const {
    return emptySlotSymbol;
}
