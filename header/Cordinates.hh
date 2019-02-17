#ifndef CORDINATES_H
#define CORDINATES_H


class Cordinates {
private:    
    int row;
    int column;

public:
    Cordinates(const int ROW, const int COL);
    const int getRow() const;
    const int getColumn() const;

    const bool equals(const Cordinates& CORDINATES) const;

    void operator = (const Cordinates& CORDINATES);
};

#endif

