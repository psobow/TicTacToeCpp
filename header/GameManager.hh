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
        PLAY = 1, 
        OPTIONS = 2, 
        EXIT = 3
    };
    enum OptionMenuDecision {
        SWITCH_SYMBOLS = 1, 
        SWITCH_STARTING_PLAYER = 2, 
        SET_BOARD_SIZE = 3, 
        SET_POINTS_FOR_VICTORY = 4, 
        EXIT_OPTIONS = 5
    };

    const static std::string EIGHT_SPACE_BARS;

    MinMaxManager *minMaxManager = MinMaxManager::getInstance();
    BoardManager *boardManager = BoardManager::getInstance();
    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();

    // Singleton
    static GameManager *instance;
    GameManager() {};
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    void gameLoop();

    Participant playGame();

    void executeOptionsDecision(const GameManager::OptionMenuDecision& DECISION);



    void printMainMenu() const;

    MainMenuDecision getMainMenuDecision(const int DECISION_INDEX) const;

    OptionMenuDecision getOptionMenuDecision(const int DECISION_INDEX) const;    
    
    Coordinates askAndReadValidHumanCoordinatesDecision() const;

    void printCheers(const Participant& winner) const;

    bool askAndReadToPlayAgain() const;

    void printOptionsMenu() const;
};

#endif