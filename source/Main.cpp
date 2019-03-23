#include <iostream>

#include "../header/GameManager.hh"



int main() {
    GameManager *gameManager = GameManager::getInstance();
    gameManager->run();
    /*
    BoardManager *board = BoardManager::getInstance();
    MinMaxManager *minmax = MinMaxManager::getInstance();

    board->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
    board->addNewCharacter(Cordinates(1,1), Participant::HUMAN);
    board->addNewCharacter(Cordinates(2,0), Participant::HUMAN);

    board->addNewCharacter(Cordinates(0,1), Participant::COMPUTER);
    board->addNewCharacter(Cordinates(2,2), Participant::COMPUTER);
    
    minmax->executeTheBestComputerMove();

    board->printBoard();
    */
    
    
    return 0;
}


/*
helpfull links:

https://www.neverstopbuilding.com/blog/minimax

https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-4-alpha-beta-pruning/

https://www.cs.cornell.edu/courses/cs312/2002sp/lectures/rec21.htm

https://www.youtube.com/watch?v=STjW3eH0Cik


Very important note:

Consider consecutive configuration: 
    -board size: 4x4
    -Points required for victory: 3

In this configuration first player can always win, no matter what his oponnent will do, if he choose correct moves obviously.

Imagine following game scenario: 

    First player go for (1,1) - (row, column)
    Second player go for (0,1)
    First player go for (2,1)
    second player go for (3,1)

    -At this point First player has several options which guarentee victory for him.
    First option:
        first player go for (2,2) 
            after this he can win game with (2,3) or (3,3)
    
    second option:
        first player go for (2,0)
            after this he can win game with (2,2) or (0,2)

Second player will not win this game no matter what he does, min max algorithm is doomed to failure from the start.
    
*/