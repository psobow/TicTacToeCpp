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

    Participant winner = Participant::NONE;
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

    void gameLoop();
    
    Cordinates askForValidHumanCordinatesDecision() const ;

    void playGame();

    bool checkIsGameFinishedAndSetWinner();

    void printWinner() const ;

    bool askToPlayAgain() const ;

    void printOptionsMenu() const;
    
    void executeOptionsDecision(const int DECISION);

};

#endif