#ifndef CORDINATES_H
#define CORDINATES_H

#include <stdexcept>

#include "GameOptionsManager.hh"

class Cordinates {
public:
    Cordinates(const int ROW, const int COL);
    void operator = (const Cordinates& CORDINATES);

    const int getRow() const;
    const int getColumn() const;
    const bool equals(const Cordinates& CORDINATES) const;

private:    
    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
    
    int row;
    int column;
};

#endif