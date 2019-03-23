#include "../header/GameOptionsManager.hh"

GameOptionsManager* GameOptionsManager::instance = nullptr;

GameOptionsManager* GameOptionsManager::getInstance(){
    if(instance == nullptr){
        instance = new GameOptionsManager();
    }
    return instance;
}

GameOptionsManager::GameOptionsManager() {}

void GameOptionsManager::setGameStartingPlayer(const GameParticipant& PARTICIPANT){
    gameStartingPlayer = PARTICIPANT;
}

void GameOptionsManager::switchHumanAndComputerChar() {
    char tempHumanChar = humanChar;
    humanChar = computerChar;
    computerChar = tempHumanChar;
}

void GameOptionsManager::setPointsRequiredForVictory(const int NEW_POINTS) {
    if (NEW_POINTS < MIN_POINTS_FOR_VICTORY || NEW_POINTS > MAX_POINTS_FOR_VICTORY) {
        std::string exceptionMessage = "Invalid new amount of points required for victory. Amount of points has to be integer from " 
        + std::to_string(MIN_POINTS_FOR_VICTORY) + " to " + std::to_string(MAX_POINTS_FOR_VICTORY) + ".\n";
        throw std::invalid_argument( exceptionMessage );
    }
    pointsRequiredForVictory = NEW_POINTS;
}

void GameOptionsManager::setBoardSize(const int NEW_BOARD_SIZE){
    if (NEW_BOARD_SIZE < MIN_BOARD_SIZE || NEW_BOARD_SIZE > MAX_BOARD_SIZE) {
        std::string exceptionMessage = "Invalid new board size. Board size has to be integer from " 
        + std::to_string(MIN_BOARD_SIZE) + " to " + std::to_string(MAX_BOARD_SIZE) + ".\n";
        throw std::invalid_argument( exceptionMessage );
    }
    boardSize = NEW_BOARD_SIZE;
}

const Participant GameOptionsManager::getEnumAssignedTo(const char CHAR) const {
    if(  (CHAR != EMPTY_SLOT_CHAR)  &&  (CHAR != humanChar)  &&  (CHAR != computerChar) ){
        std::string exceptionMessage = "Invalid char. There is no Game Participant assigned to ";
        exceptionMessage += CHAR;
        exceptionMessage += ".\n";

        throw std::invalid_argument( exceptionMessage );
    }
    
    if (CHAR == humanChar) {
        return HUMAN;

    } else if (CHAR == computerChar) {
        return COMPUTER;

    } else {
        return NONE;
    }
}

const char GameOptionsManager::getCharAssignedTo(const Participant& PARTICIPANT) const {
    if (PARTICIPANT == NONE){
        return EMPTY_SLOT_CHAR;

    } else if (PARTICIPANT == HUMAN){
        return humanChar;

    } else {
        return computerChar;
    }
}

const Participant GameOptionsManager::getGameStartingPlayer() const {
    return gameStartingPlayer;
}

const Participant GameOptionsManager::getOppositePlayer(const Participant& PARTICIPANT) const {
    return static_cast<Participant>( PARTICIPANT*(-1) );
}

const int GameOptionsManager::getPointsRequiredForVictory() const {
    return pointsRequiredForVictory;
}
const int GameOptionsManager::getBoardSize() const {
    return boardSize;
}

const int GameOptionsManager::getMinBoardSize() const{
    return MIN_BOARD_SIZE;
}

const int GameOptionsManager::getMinPointsForVictory() const{
    return MIN_POINTS_FOR_VICTORY;
}

const int GameOptionsManager::getMaxBoardSize() const{
    return MAX_BOARD_SIZE;
}

const int GameOptionsManager::getMaxPointsForVictory() const{
    return MAX_POINTS_FOR_VICTORY;
}