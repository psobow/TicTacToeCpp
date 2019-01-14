#include "../header/Cordinates.hh"

Cordinates::Cordinates(const BoardManager& boardManager, const int ROW, const int COL) {
    areCordinatesValid = true;
    if(ROW >= boardManager.getBoardSize() || ROW < 0 || 
       COL >= boardManager.getBoardSize() || COL < 0) {
           std::cerr << "Incorrect cordinates in constructor. Setting zeros\n";
           areCordinatesValid = false;
           row = 0;
           column = 0;
           return;
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

const bool Cordinates::getAreCordinatesValid() const{
    return areCordinatesValid;
}
