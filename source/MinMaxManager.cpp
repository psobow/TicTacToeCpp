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

    // in case computer starting the game, just pick (0,0) slot. this one is the best first move.
    if (boardManager->getQuantityOfTakenSlots() == 0) { 
        theBestMoveCordinates = Cordinates(0,0);

    } else {
        auto start = std::chrono::steady_clock::now();
        calculateTheBestMoveFor(Participant::COMPUTER, INITIAL_DEPTH, LOWEST_SCORE, HIGHEST_SCORE);
        auto end = std::chrono::steady_clock::now();
        
        std::cout << "Elapsed time in seconds : " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " sec\n";
    }

    return boardManager->addNewCharacter(theBestMoveCordinates, Participant::COMPUTER);
}


const int MinMaxManager::calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int depth, int alpha, int beta) {
    // Terminating condition
    const int RESULT = scoreGameFromComputerPOV(depth);
    if( RESULT != 0 || (boardManager->isAnyEmptySlot() == false) ) {
        return RESULT;
    }
    
    depth++;
    std::vector<Cordinates> availableCordinates = boardManager->getEveryEmptySlotCordinates();
    std::vector<int> scores;
    int bestScore;

    // This part execute possible moves and evaluate states of the game in order to calculate the best computer move.
    for(int i = 0; i < availableCordinates.size(); i++){
        boardManager->addNewCharacter(availableCordinates[i], TURN_TAKING_PLAYER);
        const int CURRENT_BOARD_SCORE_FROM_COMPUTER_POV = calculateTheBestMoveFor( 
            gameOptionsManager->getOppositePlayer(TURN_TAKING_PLAYER), depth, alpha, beta);
        scores.push_back(CURRENT_BOARD_SCORE_FROM_COMPUTER_POV);
        boardManager->resetSlot(availableCordinates[i]);

        // Alpha pruning
        if (TURN_TAKING_PLAYER == Participant::COMPUTER) {
            bestScore = *std::max_element( std::begin(scores), std::end(scores) );
            alpha = std::max(bestScore, alpha); // Alpha is the best value that the maximizer currently can guarantee at that level.
            if (beta <= alpha){
                break;
            }  
        // Beta pruning
        } else {
            bestScore = *std::min_element( std::begin(scores), std::end(scores) );
            beta = std::min(bestScore, beta); // Beta is the best value that the minimizer currently can guarantee at that level.
            if (beta <= alpha){
                break;
            }
        }
        
    }

    //This part is decision making part
    if(TURN_TAKING_PLAYER == Participant::COMPUTER) { // Computer is going for highiest score from his POV.
        int maxScoreIndex = getMaxValueIndex(scores);
        if(depth == 1) { // At the final point of this algorithm we want to execute the best move for computer at depth equal 1.
            theBestMoveCordinates = availableCordinates[maxScoreIndex]; 
        }
        return scores[maxScoreIndex];

// In this algoritm we assume that human is also perfect player and he always choose his the best possible move. That's huge overestimate cuz humans are dumb idiots mostly.
    } else if (TURN_TAKING_PLAYER == Participant::HUMAN) { // Human is going for lowest score from computer POV
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
        throw std::invalid_argument("Invalid argument, vector size equals zero.\n");
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
        throw std::invalid_argument("Invalid argument, vector size equals zero.\n");
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