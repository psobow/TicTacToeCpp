#include "../../libs/catch.hpp"

#include "BoardManagerTestSuite.hh"


/* TEST TEMPLATE

SCENARIO( "", "[BoardManager]" ){

    GIVEN( "BoardManager initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();

        WHEN( "CASE 1" ){

            THEN( "Result" ){
                REQUIRE( );
            }
        }
    }
}

*/

SCENARIO( "isAnyEmptySlot", "[BoardManager]" ){

    GIVEN( "BoardManager initialization, Clean up board." ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Add one symbol." ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            const bool result = boardManager->isAnyEmptySlot();
            THEN( "Result" ){
                REQUIRE( result == true );
            }
        }

        WHEN( "CASE 2: Add nine symbols (Every slot is taken)." ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);

            boardManager->addNewSymbol(Cordinates(1,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,2), COMPUTER);

            boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,2), PLAYER);

            const bool result = boardManager->isAnyEmptySlot();
            THEN( "Result" ){
                REQUIRE( result == false );
            }
        }
    }
}

SCENARIO( "resetEveryslotAndSetSize", "[BoardManager]" ){

    GIVEN( "BoardManager initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        BoardManagerTestSuite bridgeToTestClass;

        WHEN( "CASE 1: correct size" ){
            boardManager->resetEverySlotAndSetSize(5);
            const int takenSlots = boardManager->getQuantityOfTakenSlots();
            const int boardSize = bridgeToTestClass.getBoardSize();

            boardManager->resetEverySlotAndSetSize(3); // Clean-up

            THEN( "Result" ){
                REQUIRE( takenSlots == 0);
                REQUIRE( boardSize == 5);
            }
        }

        WHEN( "CASE 2: invalid size" ){
            std::string exceptionMessage;
            try {
                boardManager->resetEverySlotAndSetSize(-10);
            } catch( const std::invalid_argument& e){
                exceptionMessage = e.what();
            } 
            
            THEN( "Result" ){
                REQUIRE( exceptionMessage == "Invalid new board size. Board size has to be integer from " 
                        + std::to_string(bridgeToTestClass.getDefaultBoardSize()) + " to " 
                        + std::to_string(bridgeToTestClass.getMaxBoardSize()) + ".\n" );
            }
        }
    }
}

SCENARIO( "resetEverySlotTest", "[BoardManager]" ){

    GIVEN( "BoardManager initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Add one symbol" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->resetEverySlot();
            THEN( "Result" ){
                REQUIRE( boardManager->getQuantityOfTakenSlots() == 0 );
            }
        }
    }
}

SCENARIO( "resetSlotTest", "[BoardManager]" ){

    GIVEN( "BoardManager initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Reset already empty slot" ){
            boardManager->resetSlot(Cordinates(0,0));
            int result = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( result == 0 );
            }
        }

        WHEN( "CASE 2: Reset taken slot" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->resetSlot(Cordinates(0,0));
            int result = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( result == 0 );
            }
        }

        WHEN( "CASE 3: Add two symbols, reset one" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            boardManager->resetSlot(Cordinates(0,0));
            int result = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( result == 1 );
            }
        }
    }
}

SCENARIO( "getQuantityOfTakenSlotsTest", "[BoardManager]" ){

    GIVEN( "BoardManager, SymbolManager, Bridge initialization, Clean up board" ) {
        SymbolManager *symbolManager = SymbolManager::getInstance();
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        BoardManagerTestSuite bridgeToTestClass;
        
        
        WHEN( "CASE 1: Empty board" ){
            int howManyTakenSlots = 0;

            for(int row = 0; row < bridgeToTestClass.getBoard().size(); row++){
                for(int col = 0; col < bridgeToTestClass.getBoard().size(); col++){
                    if( bridgeToTestClass.getBoard()[row][col] != symbolManager->getCharFromEnum(NONE)){
                        howManyTakenSlots++;
                    }
                }
            }
            THEN( "Result" ){
                REQUIRE( boardManager->getQuantityOfTakenSlots() == howManyTakenSlots );
            }
        }

        WHEN( "CASE 2: Add one symbol" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            int howManyTakenSlots = 0;

            for(int row = 0; row < bridgeToTestClass.getBoard().size(); row++){
                for(int col = 0; col < bridgeToTestClass.getBoard().size(); col++){
                    if( bridgeToTestClass.getBoard()[row][col] != symbolManager->getCharFromEnum(NONE)){
                        howManyTakenSlots++;
                    }
                }
            }
            THEN( "Result" ){
                REQUIRE( boardManager->getQuantityOfTakenSlots() == howManyTakenSlots );
                REQUIRE( boardManager->getQuantityOfTakenSlots() == 1 );
            }
        }
    }
}

SCENARIO( "getEveryEmptySlotCordinatesTest", "[BoardManager]" ){

    GIVEN( "BoardManager initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Empty board" ){
            const std::vector<Cordinates> result = boardManager->getEveryEmptySlotCordinates();
            THEN( "Result" ){
                REQUIRE( result.size() == 9 );
            }
        }

        WHEN( "CASE 2: Add one symbol" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            const std::vector<Cordinates> result = boardManager->getEveryEmptySlotCordinates();
            THEN( "Result" ){
                REQUIRE( result.size() == 8 );
            }
        }
    }
}

SCENARIO( "addNewSymbolTest", "[BoardManager]" ) {

    GIVEN( "BoardManager initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Correct cordinates and player" ){
            const bool result = boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            THEN( "Result" ){
                REQUIRE( result == true );
            }
        }

        WHEN( "CASE 2: Correct cordinates and player, but slot is taken" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            const bool result = boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            THEN( "Result" ){
                REQUIRE( result == false );
            }
        }

        WHEN( "CASE 3: Correct coridnates but incorrect player" ){
            const bool result = boardManager->addNewSymbol(Cordinates(0,1), NONE);
            THEN( "Result" ){
                REQUIRE( result == false );
            }
        }

        WHEN( "CASE 4: Incorrect cordinates" ){
            std::string exceptionMessage;
            try {
                boardManager->addNewSymbol(Cordinates(-10,0), PLAYER);
            } catch( const std::invalid_argument& e){
                exceptionMessage = e.what();
            }
            THEN( "Result" ){
                REQUIRE( exceptionMessage == "Invalid cordinates" );
            }
        }

        WHEN( "CASE 5: Incorrect cordinates" ){
            std::string exceptionMessage;
            try {
                boardManager->addNewSymbol(Cordinates(0,-10), PLAYER);
            }catch( const std::invalid_argument& e){
                exceptionMessage = e.what();
            }
            THEN( "Result" ){
                REQUIRE( exceptionMessage == "Invalid cordinates" );
            }
        }

        WHEN( "CASE 6: Incorrect cordinates" ){
            const bool result = boardManager->addNewSymbol(Cordinates(10,0), PLAYER);
            THEN( "Result" ){
                REQUIRE( result == false );
            }
        }
    }
}

SCENARIO( "findWinner gernal test", "[BoardManager]" ){
    // findWinner algorithm required at least 5 taken slots on 3x3 board to search for winner

    GIVEN( "BoardManager initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        const int POINTS_FOR_VICTORY = 3;

        WHEN( "CASE 1: Not enough taken slots" ){
            const SymbolEnum result = boardManager->findWinner(POINTS_FOR_VICTORY);
            THEN( "Result" ){
                REQUIRE( result == NONE );
            }
        }

        WHEN( "CASE 2: East"){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);

            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,1), COMPUTER);

            const SymbolEnum result = boardManager->findWinner(POINTS_FOR_VICTORY);
            THEN( "Result" ){
                REQUIRE( result == PLAYER );
            }
        }

        WHEN( "CASE 3: South"){
            boardManager->addNewSymbol(Cordinates(0,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);

            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,2), PLAYER);

            const SymbolEnum result = boardManager->findWinner(POINTS_FOR_VICTORY);
            THEN( "Result" ){
                REQUIRE( result == COMPUTER );
            }
        }

        WHEN( "CASE 4: East-South"){
            boardManager->addNewSymbol(Cordinates(0,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,2), COMPUTER);

            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,2), PLAYER);

            const SymbolEnum result = boardManager->findWinner(POINTS_FOR_VICTORY);
            THEN( "Result" ){
                REQUIRE( result == COMPUTER );
            }
        }

        WHEN( "CASE 5: West-South"){
            boardManager->addNewSymbol(Cordinates(0,2), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);

            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);

            const SymbolEnum result = boardManager->findWinner(POINTS_FOR_VICTORY);
            THEN( "Result" ){
                REQUIRE( result == COMPUTER );
            }
        }
    }
}





SCENARIO( "findWinner, is possible to check slots", "[BoardManager]" ){

    GIVEN( "BoardManager, Bridge initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        BoardManagerTestSuite bridgeToTestClass;
        const int POINTS_FOR_VICTORY = 3;
        

        WHEN( "CASE 1: Is possible to check EAST slots" ){
            const bool firstResult = bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(0,0), POINTS_FOR_VICTORY);
            const bool secondResult = bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(0,1), POINTS_FOR_VICTORY);
            const bool thirdResult = bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(0,7), POINTS_FOR_VICTORY);

            bool fourthResult;

            std::string firstExceptionMessage;

            try{
                bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(-2,0), POINTS_FOR_VICTORY);
            } catch( const std::invalid_argument& e){
                firstExceptionMessage = e.what();
            }


            THEN( "firstResult" ){
                REQUIRE( firstResult == true );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == false );
            }
            THEN( "thirdResult" ){
                REQUIRE( thirdResult == false );
            }
            THEN( "fourthResult" ){
                REQUIRE( firstExceptionMessage == "Invalid cordinates" );
            }
        }

        WHEN( "CASE 2: Is possible to check SOUTH slots" ){
            const bool firstResult = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(0,0), POINTS_FOR_VICTORY);
            const bool secondResult = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(1,0), POINTS_FOR_VICTORY);
            const bool thirdResult = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(7,0), POINTS_FOR_VICTORY);

            bool fourthResult;

            std::string firstExceptionMessage;

            try{
                bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(-2,0), POINTS_FOR_VICTORY);
            } catch( const std::invalid_argument& e){
                firstExceptionMessage = e.what();
            }

            THEN( "firstResult" ){
                REQUIRE( firstResult == true );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == false );
            }
            THEN( "thirdResult" ){
                REQUIRE( thirdResult == false );
            }
            THEN( "fourthResult" ){
                REQUIRE( firstExceptionMessage == "Invalid cordinates" );
            }
        }

        WHEN( "CASE 3: Is possible to check WEST slots" ){
            const bool firstResult = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(0,2), POINTS_FOR_VICTORY);
            const bool secondResult = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(0,1), POINTS_FOR_VICTORY);
            const bool thirdResult = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(0,9), POINTS_FOR_VICTORY);

            bool fourthResult;

            std::string firstExceptionMessage;

            try{
                bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(-2,0), POINTS_FOR_VICTORY);
            }catch( const std::invalid_argument& e){
                firstExceptionMessage = e.what();
            }

            THEN( "firstResult" ){
                REQUIRE( firstResult == true );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == false );
            }
            THEN( "thirdResult" ){
                REQUIRE( thirdResult == false );
            }
            THEN( "fourthResult" ){
                REQUIRE( firstExceptionMessage == "Invalid cordinates" );
            }
        }
    }
}

SCENARIO( "findWinner, are slots not empty", "[BoardManager]" ){

    GIVEN( "BoardManager, Bridge initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        BoardManagerTestSuite bridgeToTestClass;
        const int POINTS_FOR_VICTORY = 3;
        

        WHEN( "CASE 1: Are EAST slots not empty" ){

            // slot (0,0) has been alredy checked in diffrent function, and does not affect return value of this function.

            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            const bool firstResult = bridgeToTestClass.executeAreEastSlotsNotEmpty(Cordinates(0, 0), POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
            const bool secondResult = bridgeToTestClass.executeAreEastSlotsNotEmpty(Cordinates(0, 0), POINTS_FOR_VICTORY);
       
            THEN( "secondResult" ){
                REQUIRE( firstResult == false );
            }
            THEN( "thirdResult" ){
                REQUIRE( secondResult == true );
            }
        }

        WHEN( "CASE 2: Are SOUTH slots not empty" ){
            
            // slot (0,0) has been alredy checked in diffrent function, and does not affect return value of this function.

            boardManager->addNewSymbol(Cordinates(1,0), COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreSouthSlotsNotEmpty(Cordinates(0, 0), POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreSouthSlotsNotEmpty(Cordinates(0, 0), POINTS_FOR_VICTORY);

            THEN( "secondResult" ){
                REQUIRE( firstResult == false );
            }
            THEN( "thirdResult" ){
                REQUIRE( secondResult == true );
            }
        }


        WHEN( "CASE 3: Are EAST-SOUTH slots not empty" ){

            // slot (0,0) has been alredy checked in diffrent function, and does not affect return value of this function.

            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreEastSouthSlotsNotEmpty(Cordinates(0, 0), POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(2,2), COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreEastSouthSlotsNotEmpty(Cordinates(0, 0), POINTS_FOR_VICTORY);

            THEN( "firstResult" ){
                REQUIRE( firstResult == false );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == true );
            }   
        }
        
        WHEN( "CASE 4: Are WEST-SOUTH slots not empty" ){

            // slot (0,0) has been alredy checked in diffrent function, and does not affect return value of this function.

            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreWestSouthSlotsNotEmpty(Cordinates(0, 2), POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
            const bool secondResult = bridgeToTestClass.executeAreWestSouthSlotsNotEmpty(Cordinates(0, 2), POINTS_FOR_VICTORY);
            THEN( "firstResult" ){
                REQUIRE( firstResult == false );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == true );
            }
        }
    }
}

SCENARIO( "findWinner are slots contain win state", "[BoardManager]" ){

    GIVEN( "BoardManager, Bridge initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        BoardManagerTestSuite bridgeToTestClass;
        const int POINTS_FOR_VICTORY = 3;

        WHEN( "CASE 1: Are EAST slots contain win state" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
            const bool firstResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(1,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,2), COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(1,0),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(0,2), COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(1,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,2), PLAYER);
            const bool fourthResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(1,0),POINTS_FOR_VICTORY);

            THEN( "Result" ){
                REQUIRE( firstResult  == true);
                REQUIRE( secondResult == true);

                REQUIRE( thirdResult == false);
                REQUIRE( fourthResult  == false);
            }
        }

        WHEN( "CASE 2: Are SOUTH slots contain win state" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
            const bool firstResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(0,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,1), COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,1),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,1), PLAYER);
            const bool fourthResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,1),POINTS_FOR_VICTORY);

            THEN( "Result" ){
                REQUIRE( firstResult  == true);
                REQUIRE( secondResult == true);

                REQUIRE( thirdResult == false);
                REQUIRE( fourthResult  == false);
            }
        }

        WHEN( "CASE 3: Are EAST-SOUTH slots contain win state" ){
            boardManager->addNewSymbol(Cordinates(0,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,2), COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,2), PLAYER);
            const bool secondResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,2), COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,2), PLAYER);
            const bool fourthResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0),POINTS_FOR_VICTORY);

            THEN( "Result" ){
                REQUIRE( firstResult  == true);
                REQUIRE( secondResult == true);

                REQUIRE( thirdResult  == false);
                REQUIRE( fourthResult == false);
            }
        }

        WHEN( "CASE 4: Are WEST-SOUTH slots contain win state" ){
            boardManager->addNewSymbol(Cordinates(0,2), COMPUTER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
            const bool secondResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2),POINTS_FOR_VICTORY);

            boardManager->resetEverySlot();

            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
            const bool fourthResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2),POINTS_FOR_VICTORY);

            THEN( "Result" ){
                REQUIRE( firstResult  == true);
                REQUIRE( secondResult == true);

                REQUIRE( thirdResult  == false);
                REQUIRE( fourthResult == false);
            }
        }
    }
}




const std::vector<std::vector<char>>& BoardManagerTestSuite::getBoard() const{
    return boardManager->board;
}
const int BoardManagerTestSuite::getBoardSize() const {
    return boardManager->boardSize;
}

const int BoardManagerTestSuite::getDefaultBoardSize() const{
    return boardManager->DEFAULT_BOARD_SIZE;
}
const int BoardManagerTestSuite::getMaxBoardSize() const {
    return boardManager->MAX_BOARD_SIZE;
}

const bool BoardManagerTestSuite::executeAreValidCordinates(const Cordinates& CORDINATES) const {
    return boardManager->areValidCordinates(CORDINATES);
}

const bool BoardManagerTestSuite::executeIsSlotEmpty(const Cordinates& CORDINATES) const{
    return boardManager->isSlotEmpty(CORDINATES);
}


// EAST:
const bool BoardManagerTestSuite::executeIsPossibleToCheckEastSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->isPossibleToCheckEastSlots(CORDINATES, POINTS_FOR_VICTORY);
}
const bool BoardManagerTestSuite::executeAreEastSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const {
    return boardManager->areEastSlotsNotEmpty(CORDINATES, POINTS_FOR_VICTORY);
}
const bool BoardManagerTestSuite::executeAreEastSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->areEastSlotsContainWinState(CORDINATES, POINTS_FOR_VICTORY);
}

// SOUTH:
const bool BoardManagerTestSuite::executeIsPossibleToCheckSouthSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->isPossibleToCheckSouthSlots(CORDINATES, POINTS_FOR_VICTORY);
}
const bool BoardManagerTestSuite::executeAreSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->areSouthSlotsNotEmpty(CORDINATES, POINTS_FOR_VICTORY);
}
const bool BoardManagerTestSuite::executeAreSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->areSouthSlotsContainWinState(CORDINATES, POINTS_FOR_VICTORY);
}

// EAST-SOUTH
const bool BoardManagerTestSuite::executeAreEastSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->areEastSouthSlotsNotEmpty(CORDINATES, POINTS_FOR_VICTORY);
}
const bool BoardManagerTestSuite::executeAreEastSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->areEastSouthSlotsContainWinState(CORDINATES, POINTS_FOR_VICTORY);
}

// WEST-SOUTH:
const bool BoardManagerTestSuite::executeIsPossibleToCheckWestSlots(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->isPossibleToCheckWestSlots(CORDINATES, POINTS_FOR_VICTORY);
}
const bool BoardManagerTestSuite::executeAreWestSouthSlotsNotEmpty(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->areWestSouthSlotsNotEmpty(CORDINATES, POINTS_FOR_VICTORY);
}
const bool BoardManagerTestSuite::executeAreWestSouthSlotsContainWinState(const Cordinates& CORDINATES, const int POINTS_FOR_VICTORY) const{
    return boardManager->areWestSouthSlotsContainWinState(CORDINATES, POINTS_FOR_VICTORY);
}
    