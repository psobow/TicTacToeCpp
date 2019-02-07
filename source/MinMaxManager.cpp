#include "../header/MinMaxManager.hh"

// boardManager->getBoard()[1][1];   DZIAŁA 

MinMaxManager* MinMaxManager::instance = 0;

MinMaxManager* MinMaxManager::getInstance(){
    if(instance == 0){
        instance = new MinMaxManager();
    }
    return instance;
}

MinMaxManager::MinMaxManager() {}
MinMaxManager::~MinMaxManager() {}
