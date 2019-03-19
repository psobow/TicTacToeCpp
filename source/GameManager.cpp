#include "../header/GameManager.hh"

const std::string GameManager::eightSpaceBars = "        ";

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance(){
    if(instance == nullptr){
        instance = new GameManager();
    }
    return instance;
}

void GameManager::run(){
    std::cout << "Welcome in game Tic Tac Toe!\n";
    std::cout << "You are facing unbeatable oponent, which use Min-Max algorithm to calculate next move.\n";
    std::cout << "You can try as much as you wish, but the best what you can get is a draw.\n";
    std::cout << "I would wish you good luck, but it is not going to help any way.\n";

    MainMenuDecision decision;
    int optionsDecision;
    do {
        printMainMenu();
        decision = getMainMenuDecision( MyStdIn::readNextIntFromValidScope(1,3) );
        switch (decision)
        {
            case PLAY:
                gameLoop();
                break;

            case OPTIONS:
                do {    
                    printOptionsMenu();
                    optionsDecision = MyStdIn::readNextIntFromValidScope(1,3);
                    executeOptionsDecision(optionsDecision);
                } while (optionsDecision != 3);
                break;

            case EXIT:
                std::cout << "Bye bye !\nThank you for playing my game, psobow!\n";
                break;

            default:
                break;
        }
    } while (decision != EXIT); 
}


void GameManager::printMainMenu() const {
    std::cout << "\nMAIN MENU:\n";
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
        Participant winner = playGame();
        boardManager->resetEverySlot();
        printCheers(winner);
        decision = askToPlayAgain();
    } while (decision == true);
}

Participant GameManager::playGame(){
    Cordinates decision(0,0);
    Participant winner;
    boardManager->printBoard();

    while (true) {
        
        std::cout << "(Playing as: " << gameOptionsManager->getCharAssignedTo(Participant::HUMAN) << ") Your turn: \n";
        
        decision = askForValidHumanCordinatesDecision();

        boardManager->addNewCharacter(decision, Participant::HUMAN);

        boardManager->printBoard();
        
        winner = boardManager->findWinner();
        if ( boardManager->isAnyEmptySlot() == false || winner != Participant::NONE ) {
            return winner;
        }

        std::cout << "\nComputer move:\n";

        minMaxManager->executeTheBestComputerMove();

        boardManager->printBoard();

        winner = boardManager->findWinner();
        if ( boardManager->isAnyEmptySlot() == false || winner != Participant::NONE ) {
            return winner;
        }
    }
}

Cordinates GameManager::askForValidHumanCordinatesDecision() const {
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
            std::cerr << "ERROR. Choosen cordinates are already taken!\n";
            std::cerr << "Try again: \n";
        }
    } while ( isValid == false );

    return Cordinates(row, column);
}

bool GameManager::askToPlayAgain() const {
    std::vector<char> validChars {'Y', 'y', 'N', 'n'};
    std::cout << "Do you want to play again? Y/y = Yes or N/n = No\nEnter choice: ";
    char enteredChar = MyStdIn::readNextCharWithValidation( validChars );

    return (enteredChar == 'Y' || enteredChar == 'y') ? true : false;
}

void GameManager::printCheers(const Participant& winner) const {
    switch (winner) {
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

void GameManager::printOptionsMenu() const {
    std::cout << "\n" << eightSpaceBars << "OPTIONS MENU:\n";
    std::cout << eightSpaceBars << "1. Switch players symbols ( Current setting: Human [" 
              << gameOptionsManager->getCharAssignedTo(Participant::HUMAN) << "] Computer [" 
              << gameOptionsManager->getCharAssignedTo(Participant::COMPUTER) << "] )\n";
    std::cout << eightSpaceBars << "2. Set new board size ( Current size: " << gameOptionsManager->getBoardSize() << " )\n";
    std::cout << eightSpaceBars << "3. Exit options\n";
    std::cout << eightSpaceBars << "Enter choice: ";
}

void GameManager::executeOptionsDecision(const int DECISION) {
    int minBoardSize = gameOptionsManager->getMinBoardSize();
    int maxBoardSize =  gameOptionsManager->getMaxBoardSize();

        switch (DECISION){
            case 1:
                gameOptionsManager->switchHumanAndComputerChar();
                break;
            case 2:
                std::cout << "\n" << eightSpaceBars << eightSpaceBars << "Minimal board size: " << minBoardSize << " maximum board size: " << maxBoardSize << "\n";
                std::cout << eightSpaceBars << eightSpaceBars << "Enter choice: "; 
                boardManager->resetEverySlotAndSetSize( MyStdIn::readNextIntFromValidScope( minBoardSize, maxBoardSize ) );
                break;
            case 3: // EXIT
                break;
            default:
                break;
        }
}