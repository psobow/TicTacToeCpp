#ifndef COORDINATES_H
#define COORDINATES_H

#include "GameOptionsManager.hpp"

class Coordinates 
{
public:

private:    
    int row;
    int column;
    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();

public:
    Coordinates(const int ROW, const int COL);
    void operator = (const Coordinates& COORDINATES);
    const bool equals(const Coordinates& COORDINATES) const;
    const int getRow() const;
    const int getColumn() const;
    
private:

};

#endif