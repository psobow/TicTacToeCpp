#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "BoardManager.hh"

#include <iostream>



enum MainMenuEnum {
    PLAY,
    OPTIONS,
    EXIT
};

class GameManager {

public:
    static GameManager* getInstance();
    ~GameManager();

    void printMenu();
    void getValidDecision();
    void executeMenuDecision(const MainMenuEnum& mainMenuEnum);
    
    const int getPointsForVictory() const;

private:
    GameManager(const GameManager&) = delete;
    static GameManager* instance;
    GameManager();

    int pointsForVictory = 3;


};

#endif