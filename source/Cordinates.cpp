#include "../header/Cordinates.hh"


Cordinates::Cordinates(const int ROW, const int COL) {
    if (ROW < 0 ||
        COL < 0 || 
        ROW >= gameOptionsManager->getBoardSize() || 
        COL >= gameOptionsManager->getBoardSize() ){
        
        throw std::invalid_argument("Invalid cordinates. Tried to create object with ROW: " 
        + std::to_string(ROW) + " and COL: " + std::to_string(COL) + "\n");
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