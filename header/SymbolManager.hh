#ifndef SYMBOL_MANAGER_H
#define SYMBOL_MANAGER_H

enum SymbolEnum {
    EMPTY_SLOT_SYMBOL,
    PLAYER_SYMBOL,
    COMPUTER_SYMBOL
};

class SymbolManager {
    private:
        char playerSymbol = 'O';
        char computerSymbol = 'X';
        char emptySlotSymbol = '-';

    public:
        SymbolManager();
        ~SymbolManager();

        void switchPlayerAndComputerSymbol();
        const char getCharFromEnum(SymbolEnum symbolEnum) const;
        const char getEmptySlotSymbol() const;
};

#endif