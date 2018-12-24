#include <iostream>
#include "../header/Board.hh"
using namespace std;



int main() 
{
    cout << "Hello, World!\n" << endl;



    Board board;
    board.resetEveryValueAndSetSize(4);
    board.replaceChar(0,1,'O');
    board.replaceChar(1,1,'X');
    board.printBoard();

    return 0;
}