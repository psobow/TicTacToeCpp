#include "../libs/catch.hpp"

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

static BoardManager *boardManager = BoardManager::getInstance();
static GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
static BoardManagerTestSuite bridgeToTestClass;

SCENARIO( "isAnyEmptySlot", "[BoardManager]" ){

    GIVEN( "Clean up board." ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Add one symbol." ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            const bool RESULT = boardManager->isAnyEmptySlot();
            THEN( "Result" ){
                REQUIRE( RESULT == true );
            }
        }

        WHEN( "CASE 2: Add nine symbols (Every slot is taken)." ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);

            boardManager->addNewCharacter(Coordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,2), Participant::COMPUTER);

            boardManager->addNewCharacter(Coordinates(2,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(2,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,2), Participant::HUMAN);

            const bool RESULT = boardManager->isAnyEmptySlot();
            THEN( "Result" ){
                REQUIRE( RESULT == false );
            }
        }
    }
}

SCENARIO( "resetEveryslotAndSetSize", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();
        
        WHEN( "CASE 1: correct size" ){
            boardManager->resetEverySlotAndSetSize(5);
            const int TAKEN_SLOTS = boardManager->getQuantityOfTakenSlots();
            const int BOARD_SIZE = gameOptionsManager->getBoardSize();

            boardManager->resetEverySlotAndSetSize(3); // Clean-up

            THEN( "Result" ){
                REQUIRE( TAKEN_SLOTS == 0);
                REQUIRE( BOARD_SIZE == 5);
            }
        }

        WHEN( "CASE 2: invalid size" ){
            int exceptionValidator = 0;
            try {
                boardManager->resetEverySlotAndSetSize(-10);
            } catch( const std::invalid_argument& e){
                exceptionValidator++;
            } 
            
            THEN( "Result" ){
                REQUIRE( exceptionValidator != 0 );
            }
        }
    }
}

SCENARIO( "resetEverySlotTest", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Add one symbol" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->resetEverySlot();
            THEN( "Result" ){
                REQUIRE( boardManager->getQuantityOfTakenSlots() == 0 );
            }
        }
    }
}

SCENARIO( "resetSlotTest", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Reset already empty slot" ){
            boardManager->resetSlot(Coordinates(0,0));
            const int RESULT = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( RESULT == 0 );
            }
        }

        WHEN( "CASE 2: Reset taken slot" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->resetSlot(Coordinates(0,0));
            const int RESULT = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( RESULT == 0 );
            }
        }

        WHEN( "CASE 3: Add two symbols, reset one" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,1), Participant::HUMAN);
            boardManager->resetSlot(Coordinates(0,0));
            const int RESULT = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( RESULT == 1 );
            }
        }
    }
}

SCENARIO( "getQuantityOfTakenSlotsTest", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();
        
        WHEN( "CASE 1: Empty board" ){
            int howManyTakenSlots = 0;

            for(int row = 0; row < bridgeToTestClass.getBoard().size(); row++){
                for(int col = 0; col < bridgeToTestClass.getBoard().size(); col++){
                    if( bridgeToTestClass.getBoard()[row][col] !=  gameOptionsManager->getCharAssignedTo(Participant::NONE) ){
                        howManyTakenSlots++;
                    }
                }
            }
            THEN( "Result" ){
                REQUIRE( boardManager->getQuantityOfTakenSlots() == howManyTakenSlots );
            }
        }

        WHEN( "CASE 2: Add one symbol" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            int howManyTakenSlots = 0;

            for(int row = 0; row < bridgeToTestClass.getBoard().size(); row++){
                for(int col = 0; col < bridgeToTestClass.getBoard().size(); col++){
                    if( bridgeToTestClass.getBoard()[row][col] != gameOptionsManager->getCharAssignedTo(Participant::NONE)){
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

SCENARIO( "getEveryEmptySlotCoordinatesTest", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Empty board" ){
            const std::vector<Coordinates> RESULT = boardManager->getEveryEmptySlotCoordinates();
            THEN( "Result" ){
                REQUIRE( RESULT.size() == 9 );
            }
        }

        WHEN( "CASE 2: Add one symbol" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            const std::vector<Coordinates> RESULT = boardManager->getEveryEmptySlotCoordinates();
            THEN( "Result" ){
                REQUIRE( RESULT.size() == 8 );
            }
        }
    }
}

SCENARIO( "addNewCharacterTest", "[BoardManager]" ) {

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Correct cordinates and player" ){
            const bool RESULT = boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            THEN( "Result" ){
                REQUIRE( RESULT == true );
            }
        }

        WHEN( "CASE 2: Correct cordinates and player, but slot is taken" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            const bool RESULT = boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            THEN( "Result" ){
                REQUIRE( RESULT == false );
            }
        }

        WHEN( "CASE 3: Correct coridnates but incorrect player" ){
            int exceptionValidator = 0;
            try{
                boardManager->addNewCharacter(Coordinates(0,1), Participant::NONE);
            } catch(const std::invalid_argument & e){
                exceptionValidator++;
            }
            THEN( "Result" ){
                REQUIRE( exceptionValidator != 0 );
            }
        }

        WHEN( "CASE 4: Incorrect cordinates" ){
            int exceptionValidator = 0;
            try {
                boardManager->addNewCharacter(Coordinates(-10,0), Participant::HUMAN);
            } catch( const std::invalid_argument& e){
                exceptionValidator++;
            }
            THEN( "Result" ){
                REQUIRE( exceptionValidator != 0 );
            }
        }

        WHEN( "CASE 5: Incorrect cordinates" ){
            int exceptionValidator = 0;
            try {
                boardManager->addNewCharacter(Coordinates(0,-10), Participant::HUMAN);
            }catch( const std::invalid_argument& e){
                exceptionValidator++;
            }
            THEN( "Result" ){
                REQUIRE( exceptionValidator != 0 );
            }
        }

        WHEN( "CASE 6: Incorrect cordinates" ){
            int exceptionValidator = 0;
            try {
                boardManager->addNewCharacter(Coordinates(10,0), Participant::HUMAN);
            } catch (const std::invalid_argument& e){
                exceptionValidator++;
            }
            THEN( "Result" ){
                REQUIRE( exceptionValidator != 0 );
            }
        }
    }
}

SCENARIO( "findWinner general test", "[BoardManager]" ){
    // findWinner algorithm required at least 5 taken slots on 3x3 board to search for winner

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Not enough taken slots" ){
            const Participant RESULT = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( RESULT == Participant::NONE );
            }
        }

        WHEN( "CASE 2: East"){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);

            boardManager->addNewCharacter(Coordinates(2,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,1), Participant::COMPUTER);

            const Participant RESULT = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( RESULT == Participant::HUMAN );
            }
        }

        WHEN( "CASE 3: South"){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::COMPUTER);

            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,2), Participant::HUMAN);

            const Participant RESULT = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( RESULT == Participant::COMPUTER );
            }
        }

        WHEN( "CASE 4: East-South"){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,2), Participant::COMPUTER);

            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,2), Participant::HUMAN);

            const Participant RESULT = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( RESULT == Participant::COMPUTER );
            }
        }

        WHEN( "CASE 5: West-South"){
            boardManager->addNewCharacter(Coordinates(0,2), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::COMPUTER);

            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,1), Participant::HUMAN);

            const Participant RESULT = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( RESULT == Participant::COMPUTER );
            }
        }
    }
}

SCENARIO( "findWinner, is possible to check slots", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();     

        WHEN( "CASE 1: Is possible to check EAST slots" ){
            const bool FIRST_RESULT = bridgeToTestClass.executeIsPossibleToCheckEastSlots(Coordinates(0,0));
            const bool SECOND_RESULT = bridgeToTestClass.executeIsPossibleToCheckEastSlots(Coordinates(0,1));

            int exceptionValidator1 = 0;
            try {
                bridgeToTestClass.executeIsPossibleToCheckEastSlots(Coordinates(0,7));
            } catch ( const std::invalid_argument& e){
                exceptionValidator1++;
            }

            int exceptionValidator2 = 0;
            try{
                bridgeToTestClass.executeIsPossibleToCheckEastSlots(Coordinates(-2,0));
            } catch( const std::invalid_argument& e){
                exceptionValidator2++;
            }


            THEN( "FIRST_RESULT" ){
                REQUIRE( FIRST_RESULT == true );
            }
            THEN( "SECOND_RESULT" ){
                REQUIRE( SECOND_RESULT == false );
            }
            THEN( "first exception" ){
                REQUIRE( exceptionValidator1 != 0 );
            }
            THEN( "second exception" ){
                REQUIRE( exceptionValidator2 != 0 );
            }
        }

        WHEN( "CASE 2: Is possible to check SOUTH slots" ){
            const bool FIRST_RESULT = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Coordinates(0,0));
            const bool SECOND_RESULT = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Coordinates(1,0));

            int exceptionValidator1 = 0;
            try {
                bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Coordinates(7,0));
            } catch( const std::invalid_argument& e){
                exceptionValidator1++;
            }

            int exceptionValidator2 = 0;
            try{
                bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Coordinates(-2,0));
            } catch( const std::invalid_argument& e){
                exceptionValidator2++;
            }

            THEN( "FIRST_RESULT" ){
                REQUIRE( FIRST_RESULT == true );
            }
            THEN( "SECOND_RESULT" ){
                REQUIRE( SECOND_RESULT == false );
            }
            THEN( "first exception" ){
                REQUIRE( exceptionValidator1 != 0 );
            }
            THEN( "second exception" ){
                REQUIRE( exceptionValidator2 != 0 );
            }
        }

        WHEN( "CASE 3: Is possible to check WEST slots" ){
            const bool FIRST_RESULT = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Coordinates(0,2));
            const bool SECOND_RESULT = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Coordinates(0,1));
            
            int exceptionValidator1 = 0;
            try {
                bridgeToTestClass.executeIsPossibleToCheckWestSlots(Coordinates(0,9));
            } catch ( const std::invalid_argument& e){
                exceptionValidator1++;
            }

            int exceptionValidator2 = 0;
            try{
                bridgeToTestClass.executeIsPossibleToCheckWestSlots(Coordinates(-2,0));
            }catch( const std::invalid_argument& e){
                exceptionValidator2++;
            }

            THEN( "FIRST_RESULT" ){
                REQUIRE( FIRST_RESULT == true );
            }
            THEN( "SECOND_RESULT" ){
                REQUIRE( SECOND_RESULT == false );
            }
            THEN( "first exception" ){
                REQUIRE( exceptionValidator1 != 0 );
            }
            THEN( "second exception" ){
                REQUIRE( exceptionValidator2 != 0 );
            }
        }
    }
}

SCENARIO( "findWinner, are slots not empty", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        // Coordinates at the begining has been alredy checked in BoardManager::findWinner(), and does not affect return value of this function.

        WHEN( "CASE 1: Are EAST slots not empty" ){
            Coordinates beginingCoordinates(0,0);

            boardManager->addNewCharacter(Coordinates(0,1), Participant::HUMAN);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreEastSlotsNotEmpty(beginingCoordinates);

            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreEastSlotsNotEmpty(beginingCoordinates);
       
            THEN( "SECOND_RESULT" ){
                REQUIRE( FIRST_RESULT == false );
            }
            THEN( "THIRD_RESULT" ){
                REQUIRE( SECOND_RESULT == true );
            }
        }

        WHEN( "CASE 2: Are SOUTH slots not empty" ){
            Coordinates beginingCoordinates(0,0);
            
            boardManager->addNewCharacter(Coordinates(1,0), Participant::COMPUTER);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreSouthSlotsNotEmpty(beginingCoordinates);

            boardManager->addNewCharacter(Coordinates(2,0), Participant::COMPUTER);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreSouthSlotsNotEmpty(beginingCoordinates);

            THEN( "SECOND_RESULT" ){
                REQUIRE( FIRST_RESULT == false );
            }
            THEN( "THIRD_RESULT" ){
                REQUIRE( SECOND_RESULT == true );
            }
        }


        WHEN( "CASE 3: Are EAST-SOUTH slots not empty" ){
            Coordinates beginingCoordinates(0,0);

            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreEastSouthSlotsNotEmpty(beginingCoordinates);

            boardManager->addNewCharacter(Coordinates(2,2), Participant::COMPUTER);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreEastSouthSlotsNotEmpty(beginingCoordinates);

            THEN( "FIRST_RESULT" ){
                REQUIRE( FIRST_RESULT == false );
            }
            THEN( "SECOND_RESULT" ){
                REQUIRE( SECOND_RESULT == true );
            }   
        }
        
        WHEN( "CASE 4: Are WEST-SOUTH slots not empty" ){
            Coordinates beginingCoordinates(0,2);

            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreWestSouthSlotsNotEmpty(beginingCoordinates);

            boardManager->addNewCharacter(Coordinates(2,0), Participant::HUMAN);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreWestSouthSlotsNotEmpty(beginingCoordinates);
            THEN( "FIRST_RESULT" ){
                REQUIRE( FIRST_RESULT == false );
            }
            THEN( "SECOND_RESULT" ){
                REQUIRE( SECOND_RESULT == true );
            }
        }
    }
}

SCENARIO( "findWinner are slots contain win state", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Are EAST slots contain win state" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreEastSlotsContainWinState(Coordinates(0,0));

            boardManager->addNewCharacter(Coordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,2), Participant::COMPUTER);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreEastSlotsContainWinState(Coordinates(1,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(0,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(0,2), Participant::COMPUTER);
            const bool THIRD_RESULT = bridgeToTestClass.executeAreEastSlotsContainWinState(Coordinates(0,0));

            boardManager->addNewCharacter(Coordinates(1,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,2), Participant::HUMAN);
            const bool FOURTH_RESULT = bridgeToTestClass.executeAreEastSlotsContainWinState(Coordinates(1,0));

            THEN( "Result" ){
                REQUIRE( FIRST_RESULT  == true);
                REQUIRE( SECOND_RESULT == true);

                REQUIRE( THIRD_RESULT == false);
                REQUIRE( FOURTH_RESULT  == false);
            }
        }

        WHEN( "CASE 2: Are SOUTH slots contain win state" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::HUMAN);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreSouthSlotsContainWinState(Coordinates(0,0));

            boardManager->addNewCharacter(Coordinates(0,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,1), Participant::COMPUTER);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreSouthSlotsContainWinState(Coordinates(0,1));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::COMPUTER);
            const bool THIRD_RESULT = bridgeToTestClass.executeAreSouthSlotsContainWinState(Coordinates(0,0));

            boardManager->addNewCharacter(Coordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,1), Participant::HUMAN);
            const bool FOURTH_RESULT = bridgeToTestClass.executeAreSouthSlotsContainWinState(Coordinates(0,1));

            THEN( "Result" ){
                REQUIRE( FIRST_RESULT  == true);
                REQUIRE( SECOND_RESULT == true);

                REQUIRE( THIRD_RESULT == false);
                REQUIRE( FOURTH_RESULT  == false);
            }
        }

        WHEN( "CASE 3: Are EAST-SOUTH slots contain win state" ){
            boardManager->addNewCharacter(Coordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,2), Participant::COMPUTER);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Coordinates(0,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(2,2), Participant::HUMAN);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Coordinates(0,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,2), Participant::COMPUTER);
            const bool THIRD_RESULT = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Coordinates(0,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,2), Participant::HUMAN);
            const bool FOURTH_RESULT = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Coordinates(0,0));

            THEN( "Result" ){
                REQUIRE( FIRST_RESULT  == true);
                REQUIRE( SECOND_RESULT == true);

                REQUIRE( THIRD_RESULT  == false);
                REQUIRE( FOURTH_RESULT == false);
            }
        }

        WHEN( "CASE 4: Are WEST-SOUTH slots contain win state" ){
            boardManager->addNewCharacter(Coordinates(0,2), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::COMPUTER);
            const bool FIRST_RESULT = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Coordinates(0,2));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::HUMAN);
            const bool SECOND_RESULT = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Coordinates(0,2));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::COMPUTER);
            const bool THIRD_RESULT = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Coordinates(0,2));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Coordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Coordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Coordinates(2,0), Participant::HUMAN);
            const bool FOURTH_RESULT = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Coordinates(0,2));

            THEN( "Result" ){
                REQUIRE( FIRST_RESULT  == true);
                REQUIRE( SECOND_RESULT == true);

                REQUIRE( THIRD_RESULT  == false);
                REQUIRE( FOURTH_RESULT == false);
            }
        }
    }
}




const std::vector<std::vector<char>>& BoardManagerTestSuite::getBoard() const{
    return boardManager->board;
}



// EAST:
const bool BoardManagerTestSuite::executeIsPossibleToCheckEastSlots(const Coordinates& COORDINATES) const{
    return boardManager->isPossibleToCheckEastSlots(COORDINATES);
}
const bool BoardManagerTestSuite::executeAreEastSlotsNotEmpty(const Coordinates& COORDINATES) const {
    return boardManager->areEastSlotsNotEmpty(COORDINATES);
}
const bool BoardManagerTestSuite::executeAreEastSlotsContainWinState(const Coordinates& COORDINATES) const{
    return boardManager->areEastSlotsContainWinState(COORDINATES);
}

// SOUTH:
const bool BoardManagerTestSuite::executeIsPossibleToCheckSouthSlots(const Coordinates& COORDINATES) const{
    return boardManager->isPossibleToCheckSouthSlots(COORDINATES);
}
const bool BoardManagerTestSuite::executeAreSouthSlotsNotEmpty(const Coordinates& COORDINATES) const{
    return boardManager->areSouthSlotsNotEmpty(COORDINATES);
}
const bool BoardManagerTestSuite::executeAreSouthSlotsContainWinState(const Coordinates& COORDINATES) const{
    return boardManager->areSouthSlotsContainWinState(COORDINATES);
}

// EAST-SOUTH
const bool BoardManagerTestSuite::executeAreEastSouthSlotsNotEmpty(const Coordinates& COORDINATES) const{
    return boardManager->areEastSouthSlotsNotEmpty(COORDINATES);
}
const bool BoardManagerTestSuite::executeAreEastSouthSlotsContainWinState(const Coordinates& COORDINATES) const{
    return boardManager->areEastSouthSlotsContainWinState(COORDINATES);
}

// WEST-SOUTH:
const bool BoardManagerTestSuite::executeIsPossibleToCheckWestSlots(const Coordinates& COORDINATES) const{
    return boardManager->isPossibleToCheckWestSlots(COORDINATES);
}
const bool BoardManagerTestSuite::executeAreWestSouthSlotsNotEmpty(const Coordinates& COORDINATES) const{
    return boardManager->areWestSouthSlotsNotEmpty(COORDINATES);
}
const bool BoardManagerTestSuite::executeAreWestSouthSlotsContainWinState(const Coordinates& COORDINATES) const{
    return boardManager->areWestSouthSlotsContainWinState(COORDINATES);
}
    
