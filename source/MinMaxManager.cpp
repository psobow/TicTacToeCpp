#include "../header/MinMaxManager.hh"

MinMaxManager* MinMaxManager::instance = nullptr;

MinMaxManager* MinMaxManager::getInstance(){
    if(instance == nullptr){
        instance = new MinMaxManager();
    }
    return instance;
}

const bool MinMaxManager::executeTheBestComputerMove(){
    if (boardManager->isAnyEmptySlot() == false) return false;

    const int INITIAL_DEPTH = 0;

    // in case computer first move on the board, just pick (0,0) slot. this one is the best first move.
    if (boardManager->getQuantityOfTakenSlots() == 0) { 
        theBestMoveCordinates = Cordinates(0,0);

    } else {
        calculateTheBestMoveFor(Participant::COMPUTER, INITIAL_DEPTH);
    }

    return boardManager->addNewCharacter(theBestMoveCordinates, Participant::COMPUTER);
}

// this function execute every possible move and evaluate states of the game in order to calculate the best computer move.
const int MinMaxManager::calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int depth) {
    const int RESULT = scoreGameFromComputerPOV(depth);
    if( RESULT != 0 || (boardManager->isAnyEmptySlot() == false) ) {
        return RESULT;
    }
    
    depth++;
    std::vector<Cordinates> availableCordinates = boardManager->getEveryEmptySlotCordinates();
    std::vector<int> scores;

    for(int i = 0; i < availableCordinates.size(); i++){
        boardManager->addNewCharacter(availableCordinates[i], TURN_TAKING_PLAYER);
        const int CURRENT_BOARD_SCORE = calculateTheBestMoveFor( gameOptionsManager->getOppositePlayer(TURN_TAKING_PLAYER), depth );
        scores.push_back(CURRENT_BOARD_SCORE);
        boardManager->resetSlot(availableCordinates[i]);
    }

    if(TURN_TAKING_PLAYER == Participant::COMPUTER) { // this is the max calculation.
        int maxScoreIndex = getMaxValueIndex(scores);
        if(depth == 1) { // we are interested in only with move at depth equals one.
            theBestMoveCordinates = availableCordinates[maxScoreIndex]; 
        }
        return scores[maxScoreIndex];

    } else if (TURN_TAKING_PLAYER == Participant::HUMAN) { // this is the min calculation.
        int minScoreIndex = getMinValueIndex(scores);
        return scores[minScoreIndex];
    } 
}

const int MinMaxManager::scoreGameFromComputerPOV(const int DEPTH) const {
    const Participant winner = boardManager->findWinner();

    if (winner == Participant::COMPUTER){
        return HIGHEST_SCORE - DEPTH;

    } else if (winner == Participant::NONE){
        return 0;

    } else {
        return -HIGHEST_SCORE + DEPTH;
    }
}

const int MinMaxManager::getMaxValueIndex(const std::vector<int>& VEC) const {
    if ( VEC.size() == 0 ){
        throw std::invalid_argument("Invalid argument, recived vector size equals zero.\n");
    }

    int result = 0;
    int maxValue = VEC[0];
    for(int i = 1; i < VEC.size(); i++){
        if(VEC[i] > maxValue){
            maxValue = VEC[i];
            result = i;
        }
    }
    return result;
}

const int MinMaxManager::getMinValueIndex(const std::vector<int>& VEC) const {
    if ( VEC.size() == 0 ) {
        throw std::invalid_argument("Invalid argument, recived vector size equals zero.\n");
    }
    
    int result = 0;
    int minValue = VEC[0];
    for(int i = 1; i < VEC.size(); i++){
        if(VEC[i] < minValue){
            minValue = VEC[i];
            result = i;
        }
    }
    return result;
}