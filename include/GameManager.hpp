#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "MinMaxManager.hpp"
#include "MyStdIn.hpp"


class GameManager 
{
public:

private:
    static GameManager *instance;
    const static std::string EIGHT_SPACE_BARS;

    MinMaxManager *minMaxManager = MinMaxManager::getInstance();
    BoardManager *boardManager = BoardManager::getInstance();
    GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
    
    const int MAIN_MENU_FIRST_OPTION_INDEX = 1;
    const int MAIN_MENU_LAST_OPTION_INDEX = 3;
    const int OPTION_MENU_FIRST_INDEX = 1;
    const int OPTION_MENU_LAST_INDEX = 5;

    enum MainMenuDecision 
    {
        PLAY = 1, 
        OPTIONS = 2, 
        EXIT = 3
    };
    enum OptionMenuDecision 
    {
        SWITCH_SYMBOLS = 1, 
        SWITCH_STARTING_PLAYER = 2, 
        SET_BOARD_SIZE = 3, 
        SET_POINTS_FOR_VICTORY = 4, 
        EXIT_OPTIONS = 5
    };

public:
    static GameManager* getInstance();
    ~GameManager() {};
    void run();

private:
    // Singleton
    GameManager() {};
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    void gameLoop();
    Participant playGame();
    void executeOptionsDecision(const GameManager::OptionMenuDecision& DECISION);
    
    void printMainMenu() const;
    void printCheers(const Participant& winner) const;
    void printOptionsMenu() const;
    MainMenuDecision getMainMenuDecision(const int DECISION_INDEX) const;
    OptionMenuDecision getOptionMenuDecision(const int DECISION_INDEX) const; 
    Coordinates askAndReadValidHumanCoordinatesDecision() const;
    bool askAndReadToPlayAgain() const;
};
#endif