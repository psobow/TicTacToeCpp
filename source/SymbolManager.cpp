#include "../header/SymbolManager.hh"

SymbolManager* SymbolManager::instance = 0;

SymbolManager* SymbolManager::getInstance(){
    if(instance == 0){
        instance = new SymbolManager();
    }
    return instance;
}

SymbolManager::SymbolManager() {};
SymbolManager::~SymbolManager() {};

void SymbolManager::switchPlayerAndComputerSymbol() {
    char tempPlayerSymbol = playerSymbol;
    playerSymbol = computerSymbol;
    computerSymbol = tempPlayerSymbol;
}

const char SymbolManager::getCharFromEnum(const SymbolEnum& SYMBOL) const {
    if (SYMBOL == EMPTY_SLOT){
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
        return EMPTY_SLOT;
    }
}