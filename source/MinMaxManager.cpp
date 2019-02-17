#include "../header/MinMaxManager.hh"


MinMaxManager* MinMaxManager::instance = nullptr;

MinMaxManager* MinMaxManager::getInstance(){
    if(instance == nullptr){
        instance = new MinMaxManager();
    }
    return instance;
}

MinMaxManager::MinMaxManager() {}
MinMaxManager::~MinMaxManager() {}

const int MinMaxManager::scoreGameFromComputerPOV(const int depth) const {
    const SymbolEnum winner = boardManager->findWinner(gameManager->getPointsForVictory());

    if (winner == COMPUTER){
        return 100 - depth;
    } else if (winner == NONE){
        return 0;
    } else {
        return -100 + depth;
    }
}

void MinMaxManager::mainMinMax(){

    makeNextMove(COMPUTER, 0);

    boardManager->addNewSymbol(computerChoice, COMPUTER);
}

// make virtual moves and evaluate states of the game in order to calculate the best move for computer.
// algorytm poniżej wyjebie sie na wielu wątkach !!   trzeba jakoś zrobić zeby funkcja makeNextMove zwracała Cordinaty, zamiast zapisywała je do pola 
// computerChoice. (to nadpisywanie pola computerChoice zabije ten algorytm na wielu wątkach)
//TODO: dodać głębokość do algorytmu...

int MinMaxManager::makeNextMove(const SymbolEnum& turnTakingPlayer, int depth) {

    const int result = scoreGameFromComputerPOV(depth);
    if( result != 0 || (boardManager->isAnyEmptySlot() == false) ) {
        return result;
    }

    depth++;

    std::vector<Cordinates> availableCordinates = boardManager->getEveryEmptySlotCordinates();
    std::vector<int> scores;

    for(int i = 0; i < availableCordinates.size(); i++){
        boardManager->addNewSymbol(availableCordinates[i], turnTakingPlayer);

        int currentBoardState = makeNextMove( symbolManager->getOppositePlayer(turnTakingPlayer), depth );
        scores.push_back(currentBoardState);
        boardManager->resetSlot(availableCordinates[i]);


    }
    

    if(turnTakingPlayer == COMPUTER){
        // this is the max calculation.
        int maxScoreIndex = getMaxValueIndex(scores);
        computerChoice = availableCordinates[maxScoreIndex];
        depth--;
        return scores[maxScoreIndex];

    } else if (turnTakingPlayer == PLAYER){
        // this is the min calculation.
        int minScoreIndex = getMinValueIndex(scores);
        depth--;
        return scores[minScoreIndex];
    } 
}

    /* MIN MAX
    - Robimy back up planszy ( w funkcji nadrzędnej!!)
    - wywołujemy funkcje rekurencyjną (makeNextMove):

        1. jeżeli gra jest wygrana/przegrana, LUB nie ma już slota no to jest koniec. wczytujemy back up. zwracamy wynik punktowy.
        
        2. tworzymy sobie dwa vectory, jeden na wszystkie wolne sloty(available moves). drugi vector na wyniki punktowe dla każdego stanu gry po wykonaniu ruchu
        dla każdego wolnego slota.

        3. w pętli dla wszystkich wolnych slotów
            w każdej iteracji wykonujemy addNewSymbol(turn taking player SYMBOL) dla kolejnego wolnego slota.
            w każdej iteracji wykonujemy scores =  -rekurencyjne wywołanie makeNextMove(getOppositePlayer, ) .
                

        # do the min max calculation...  
        zwracamy odpowiedni wynik do wyżej. 
        jeżeli to tura człowieka to z perspektywy komputera człowiek wybierze najmniejszy wynik.
        jeżeli to tura komputera to zwracamy największy wynik.
    */




int MinMaxManager::getMaxValueIndex(const std::vector<int>& vec) const {
    if ( vec.size() == 0 ) return -1;

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


int MinMaxManager::getMinValueIndex(const std::vector<int>& vec) const {
    if ( vec.size() == 0 ) return -1;

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