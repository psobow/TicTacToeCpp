#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stdexcept>

#include "BoardManager.hh"
#include "MyStdIn.hh"


class GameManager {
public:
    static GameManager* getInstance();
    ~GameManager() {};

    void startGame();

private:
    enum MainMenuDecision {
        PLAY = 1, OPTIONS = 2, EXIT = 3
    };

    // Singleton
    static GameManager *instance;
    GameManager()  {};
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    void printMainMenu() const;
    MainMenuDecision getMainMenuDecision(const int DECISION_INDEX) const;




    

};

#endif