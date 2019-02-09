#ifndef SYMBOL_MANAGER_H
#define SYMBOL_MANAGER_H

enum SymbolEnum {
    COMPUTER = -1,
    NONE = 0,
    PLAYER = 1
};

class SymbolManager {
public:
    static SymbolManager* getInstance();
    ~SymbolManager();

    void switchPlayerAndComputerSymbol();
    const char getCharFromEnum(const SymbolEnum& SYMBOL) const;
    const SymbolEnum getEnumFromChar(const char CHAR) const;

private:
    static SymbolManager* instance;
    SymbolManager();

    char playerSymbol = 'O';
    char computerSymbol = 'X';
    const char emptySlotSymbol = '-';
};

#endif