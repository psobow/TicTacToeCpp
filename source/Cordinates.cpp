#include "../header/Cordinates.hh"

Cordinates::Cordinates(const int ROW, const int COL) {
    if (ROW < 0 || COL < 0){
        throw std::invalid_argument("Invalid cordinates");
    }
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

void Cordinates::operator = (const Cordinates& CORDINATES){
    row = CORDINATES.getRow();
    column = CORDINATES.getColumn();
}