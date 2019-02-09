#include "../header/Cordinates.hh"

Cordinates::Cordinates(const int ROW, const int COL) {
    row = ROW;
    column = COL;
}

const int Cordinates::getRow() const {
    return row;
}

const int Cordinates::getColumn() const {
    return column;
}

const bool Cordinates::equals(const Cordinates& CORDINATES) const{
    return (row == CORDINATES.getRow() && column == CORDINATES.getColumn());
}

