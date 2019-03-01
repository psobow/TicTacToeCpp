#ifndef CORDINATES_H
#define CORDINATES_H

#include <stdexcept>

class Cordinates {
private:    
    int row;
    int column;

public:
    Cordinates(const int ROW, const int COL);
    void operator = (const Cordinates& CORDINATES);
    const int getRow() const;
    const int getColumn() const;
    const bool equals(const Cordinates& CORDINATES) const;
};

#endif