#include "../header/GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance(){
    if(instance == nullptr){
        instance = new GameManager();
    }
    return instance;
}

void GameManager::run(){
    std::cout << "Welcome in game Tic Tac Toe!\n";
    std::cout << "You are facing unbeatable oponent, which has implemenented Min-Max algorithm.\n";
    std::cout << "You can try as much as you wish, but the best what you can get is a draw.\n";
    std::cout << "I would wish you good luck, but it is not going to help any way.\n\n";

    MainMenuDecision decision;
    do {
        printMainMenu();
        decision = getMainMenuDecision( MyStdIn::readNextIntFromValidScope(1,3) );
        std::cout << "\n\n";
        switch (decision)
        {
            case PLAY:
                gameLoop();
                break;

            case OPTIONS:
            std::cout << "To be implemented...\n";
            // print options 
            // executeChoice
            // clear screen
                break;

            case EXIT:
            std::cout << "Bye bye !\nThank you for playing my game, psobow!";
                break;

            default:
                break;
        }
    } while (decision != EXIT); 
}


void GameManager::printMainMenu() const {
    std::cout << "MAIN MENU:\n";
    std::cout << "1.Play\n";
    std::cout << "2.Options\n";
    std::cout << "3.Exit\n";
    std::cout << "Enter choice: ";
}

GameManager::MainMenuDecision GameManager::getMainMenuDecision(const int DECISION_INDEX) const {
    if( DECISION_INDEX < 1 || DECISION_INDEX > 3){
        throw std::invalid_argument("Invalid index for main menu decision.\n");
    }
    return static_cast<GameManager::MainMenuDecision> (DECISION_INDEX);
}

void GameManager::gameLoop() {
    bool decision;
    do {
        playGame();
        boardManager->resetEverySlot();
        printWinner();
        decision = askToPlayAgain();
    } while (decision == true);
}

bool GameManager::checkIsGameFinishedAndSetWinner() {
    if (boardManager->isAnyEmptySlot() == false){
        winner = Participant::NONE;
        return true;
    }
    winner = boardManager->findWinner(); 
    return winner != Participant::NONE;
}

void GameManager::playGame(){
    Cordinates decision(0,0);
    boardManager->printBoard();

    while (true) {
        
        std::cout << "(Playing as: " << gameOptionsManager->getCharAssignedTo(Participant::HUMAN) << ") Your turn: \n";
        
        decision = getValidHumanCordinatesDecision();

        boardManager->addNewCharacter(decision, Participant::HUMAN);

        boardManager->printBoard();

        if ( checkIsGameFinishedAndSetWinner() ) break;

        std::cout << "\nComputer move:\n";

        minMaxManager->executeTheBestComputerMove();

        boardManager->printBoard();

        if ( checkIsGameFinishedAndSetWinner() ) break;
    }
}

Cordinates GameManager::getValidHumanCordinatesDecision(){
    int lastValidIndex = gameOptionsManager->getBoardSize()-1;
    int row = 0, column = 0;
    bool isValid = false;

    do {         
        std::cout << "Enter ROW: ";  
        row = MyStdIn::readNextIntFromValidScope( 0, lastValidIndex );

        std::cout << "Enter COLUMN: ";
        column = MyStdIn::readNextIntFromValidScope( 0, lastValidIndex );

        if( boardManager->isSlotEmpty(Cordinates(row, column)) ){
            isValid = true;
        } else {
            isValid = false;
            std::cout << "ERROR. Choosen cordinates are alredy taken!\n";
        }
    } while ( isValid == false );

    return Cordinates(row, column);
}

void GameManager::printWinner(){
    switch (this->winner)
    {
        case Participant::HUMAN:
            std::cout << "You had to cheat to acomplished that...\n";
            break;
        case Participant::NONE:
            std::cout << "Excelent! You have managed to draw!\n";
            break;
        case Participant::COMPUTER:
            std::cout << "Eazy game for computer.\n";
            break;

        default:
            break;
    }
}

bool GameManager::askToPlayAgain(){
    std::vector<char> validChars {'Y', 'y', 'N', 'n'};
    std::cout << "Do you want to play again? Y/y = Yes or N/n = No\nEnter choice: ";
    char enteredChar = MyStdIn::readNextCharWithValidation( validChars );

    return (enteredChar == 'Y' || enteredChar == 'y') ? true : false;
}