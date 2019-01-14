#ifndef CORDINATES_H
#define CORDINATES_H
#include "BoardManager.hh"

class BoardManager;

class Cordinates {
private:    
    bool areCordinatesValid;
    int row;
    int column;

public:
    Cordinates(const BoardManager& boardManager, const int ROW, const int COL);
    const int getRow() const;
    const int getColumn() const;
    const bool getAreCordinatesValid() const;
};

#endif