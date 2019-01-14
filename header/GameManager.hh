#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>
#include "BoardManager.hh"

enum MainMenuEnum {
    PLAY,
    OPTIONS,
    EXIT
};

class GameManager
{
    private:
       BoardManager boardManager;

    public:
        GameManager();
        ~GameManager();

        void printMenu();
        void getValidDecision();
        void executeMenuDecision(MainMenuEnum mainMenuEnum);
};

#endif