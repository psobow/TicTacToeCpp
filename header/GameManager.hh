#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>
#include "BoardManager.hh"


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

private:
    static GameManager* instance;
    GameManager();


};

#endif