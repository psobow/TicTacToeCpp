#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "MinMaxManager.hh"
#include "MyStdIn.hh"


class GameManager {
public:
    static GameManager* getInstance();
    ~GameManager() {};

    void run();

private:
    enum MainMenuDecision {
        PLAY = 1, OPTIONS = 2, EXIT = 3
    };
    enum OptionMenuDecision {
        SWITCH_SYMBOLS = 1, SET_BOARD_SIZE = 2, EXIT_OPTIONS = 3
    };

    const static std::string eightSpaceBars;
    MinMaxManager *minMaxManager = MinMaxManager::getInstance();
    BoardManager *boardManager = BoardManager::getInstance();
    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();

    // Singleton
    static GameManager *instance;
    GameManager()  {};
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    void printMainMenu() const;
    MainMenuDecision getMainMenuDecision(const int DECISION_INDEX) const;

    OptionMenuDecision getOptionMenuDecision(const int DECISION_INDEX) const;

    void gameLoop();
    
    Cordinates askForValidHumanCordinatesDecision() const ;

    Participant playGame();

    void printCheers(const Participant& winner) const ;

    bool askToPlayAgain() const ;

    void printOptionsMenu() const;
    
    void executeOptionsDecision(const GameManager::OptionMenuDecision& DECISION);

};

#endif