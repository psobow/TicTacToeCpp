#ifndef MINMAX_MANAGER_H
#define MINMAX_MANAGER_H

#include "BoardManager.hh"

class MinMaxManager {
public:
    static MinMaxManager* getInstance();
    ~MinMaxManager();

private:
    static MinMaxManager* instance;
    MinMaxManager();

    const BoardManager *boardManager = BoardManager::getInstance();
};



#endif