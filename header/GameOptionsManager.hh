#ifndef GAME_OPTIONS_MANAGER_H
#define GAME_OPTIONS_MANAGER_H

#include <string>
#include <stdexcept>


class GameOptionsManager {
public:
    enum GameParticipant {
        COMPUTER = -1, NONE = 0, HUMAN = 1
    };

    static GameOptionsManager* getInstance();
    ~GameOptionsManager() {};
    
    void switchHumanAndComputerChar();

    void setPointsRequiredForVictory(const int NEW_POINTS);
    void setBoardSize(const int NEW_BOARD_SIZE);

    const int getPointsRequiredForVictory() const;
    const int getBoardSize() const;

    const int getMinBoardSize() const;
    const int getMaxBoardSize() const;

    const int getMinPointsForVictory() const;
    const int getMaxPointsForVictory() const;

    const char getCharAssignedTo(const GameParticipant& PARTICIPANT) const;
    const GameParticipant getEnumAssignedTo(const char CHAR) const;
    const GameParticipant getOppositePlayer(const GameParticipant& PARTICIPANT) const;

private:
    const char EMPTY_SLOT_CHAR = '-';
    const char DEFAULT_HUMAN_CHAR = 'O';
    const char DEFAULT_COMPUTER_CHAR = 'X';

    const int MIN_BOARD_SIZE = 3;
    const int MAX_BOARD_SIZE = 9;

    const int MIN_POINTS_FOR_VICTORY = 3;
    const int MAX_POINTS_FOR_VICTORY = 9;

    int pointsRequiredForVictory;
    int boardSize;

    char humanChar;
    char computerChar;

    // Singleton
    static GameOptionsManager *instance;
    GameOptionsManager();
    GameOptionsManager(const GameOptionsManager&) = delete;
    GameOptionsManager& operator=(const GameOptionsManager&) = delete;
};

typedef GameOptionsManager::GameParticipant Participant;

#endif