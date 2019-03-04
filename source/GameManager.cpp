#include "../header/GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance(){
    if(instance == nullptr){
        instance = new GameManager();
    }
    return instance;
}

void GameManager::printMainMenu() const {
    std::cout << "      Welcome in game Tic Tac Toe!\n";
    std::cout << "      MAIN MENU:\n";
    std::cout << "      1.Play\n";
    std::cout << "      2.Option\n";
    std::cout << "      3.Exit\n";
    std::cout << "      Enter choice: ";
}

GameManager::MainMenuDecision GameManager::getMainMenuDecision(const int DECISION_INDEX) const {
    if( DECISION_INDEX < 1 || DECISION_INDEX > 3){
        throw std::invalid_argument("Invalid decision index for main menu decision.\n");
    }

    switch (DECISION_INDEX) {
        case 1:
            return MainMenuDecision::PLAY;
            break;
        case 2:
            return MainMenuDecision::OPTIONS;
            break;
        case 3:
            return MainMenuDecision::EXIT;
            break;
    }
}

void GameManager::startGame(){
    MainMenuDecision decision;
    do {
        printMainMenu();
        decision = getMainMenuDecision( MyStdIn::readNextIntFromValidScope(1,3) );
        switch (decision)
        {
            case PLAY:
            // gameLoop()
                break;

            case OPTIONS:
            // print options 
            // ask what to do
                break;

            case EXIT:
            // say good bye()
                break;

            default:
                break;
        }
    } while (decision != EXIT); 
}
