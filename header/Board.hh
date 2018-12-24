#include <vector>


class Board
{
private:
    const int DEFAULT_BOARD_SIZE = 3;
    std::vector<std::vector<char>> board_vec;
    int boardSize;

public:
    Board();
    ~Board();

    void resetEveryValueAndSetSize(const int BOARD_SIZE);
    void resetEveryValue();
    void printBoard();
    void replaceChar(const int row, const int col, const char value);
    
    
};
