#include "../header/SymbolManager.hh"

SymbolManager* SymbolManager::instance = nullptr;

SymbolManager* SymbolManager::getInstance(){
    if(instance == nullptr){
        instance = new SymbolManager();
    }
    return instance;
}


void SymbolManager::switchPlayerAndComputerSymbol() {
    char tempPlayerSymbol = playerSymbol;
    playerSymbol = computerSymbol;
    computerSymbol = tempPlayerSymbol;
}

const char SymbolManager::getCharFromEnum(const SymbolEnum& SYMBOL) const {
    if (SYMBOL == NONE){
        return emptySlotSymbol;
    } else if (SYMBOL == PLAYER){
        return playerSymbol;
    } else {
        return computerSymbol;
    }
}

const SymbolEnum SymbolManager::getEnumFromChar(const char CHAR) const {
    if (CHAR == playerSymbol) {
        return PLAYER;
    } else if (CHAR == computerSymbol) {
        return COMPUTER;
    } else {
        return NONE;
    }
}

const SymbolEnum SymbolManager::getOppositePlayer(const SymbolEnum& SYMBOL) const {
    return static_cast<SymbolEnum>(SYMBOL*(-1));
}