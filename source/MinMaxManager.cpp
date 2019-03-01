#include "../header/MinMaxManager.hh"


MinMaxManager* MinMaxManager::instance = nullptr;

MinMaxManager* MinMaxManager::getInstance(){
    if(instance == nullptr){
        instance = new MinMaxManager();
    }
    return instance;
}

const int MinMaxManager::scoreGameFromComputerPOV(const int depth) const {
    const SymbolEnum winner = boardManager->findWinner(gameManager->getPointsForVictory());
    if (winner == COMPUTER){
        return HIGHEST_SCORE - depth;
    } else if (winner == NONE){
        return 0;
    } else {
        return -HIGHEST_SCORE + depth;
    }
}

void MinMaxManager::executeTheBestComputerMove(){
    if (boardManager->isAnyEmptySlot() == false) return;

    const int initialDepth = 0;
    if (boardManager->getQuantityOfTakenSlots() == 0) { // in case computer first move on the board, just pick (0,0) slot. this one is the best first move.
        theBestMoveCordinates = Cordinates(0,0);
    } else {
        calculateTheBestMove(COMPUTER, initialDepth);
    }
    boardManager->addNewSymbol(theBestMoveCordinates, COMPUTER);
}

// execute every possible move and evaluate states of the game in order to calculate the best computer move.
const int MinMaxManager::calculateTheBestMove(const SymbolEnum& turnTakingPlayer, int depth) {
    const int result = scoreGameFromComputerPOV(depth);
    if( result != 0 || (boardManager->isAnyEmptySlot() == false) ) {
        return result;
    }
    depth++;
    
    std::vector<Cordinates> availableCordinates = boardManager->getEveryEmptySlotCordinates();
    std::vector<int> scores;

    for(int i = 0; i < availableCordinates.size(); i++){
        boardManager->addNewSymbol(availableCordinates[i], turnTakingPlayer);
        int currentBoardState = calculateTheBestMove( symbolManager->getOppositePlayer(turnTakingPlayer), depth );
        scores.push_back(currentBoardState);
        boardManager->resetSlot(availableCordinates[i]);
    }

    if(turnTakingPlayer == COMPUTER){
        // this is the max calculation.
        int maxScoreIndex = getMaxValueIndex(scores);
        if(depth == 1) { // this is the only move we are interested in.
            theBestMoveCordinates = availableCordinates[maxScoreIndex]; 
        }
        return scores[maxScoreIndex];

    } else if (turnTakingPlayer == PLAYER){
        // this is the min calculation.
        int minScoreIndex = getMinValueIndex(scores);
        return scores[minScoreIndex];
    } 
}


const int MinMaxManager::getMaxValueIndex(const std::vector<int>& vec) const {
    if ( vec.size() == 0 ){
        throw std::invalid_argument("Invalid argument, vector size equals zero.");
    }

    int result = 0;
    int maxValue = vec[0];
    for(int i = 1; i < vec.size(); i++){
        if(vec[i] > maxValue){
            maxValue = vec[i];
            result = i;
        }
    }
    return result;
}


const int MinMaxManager::getMinValueIndex(const std::vector<int>& vec) const {
    if ( vec.size() == 0 ) {
        throw std::invalid_argument("Invalid argument, vector size equals zero.");
    }
    
    int result = 0;
    int minValue = vec[0];
    for(int i = 1; i < vec.size(); i++){
        if(vec[i] < minValue){
            minValue = vec[i];
            result = i;
        }
    }
    return result;
}