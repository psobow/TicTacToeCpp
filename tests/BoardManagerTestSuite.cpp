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

static BoardManager *boardManager = BoardManager::getInstance();
static GameOptionsManager *gameOptionsManager = GameOptionsManager::getInstance();
static BoardManagerTestSuite bridgeToTestClass;

SCENARIO( "isAnyEmptySlot", "[BoardManager]" ){

    GIVEN( "Clean up board." ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Add one symbol." ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            const bool result = boardManager->isAnyEmptySlot();
            THEN( "Result" ){
                REQUIRE( result == true );
            }
        }

        WHEN( "CASE 2: Add nine symbols (Every slot is taken)." ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);

            boardManager->addNewCharacter(Cordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,2), Participant::COMPUTER);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::HUMAN);

            const bool result = boardManager->isAnyEmptySlot();
            THEN( "Result" ){
                REQUIRE( result == false );
            }
        }
    }
}

SCENARIO( "resetEveryslotAndSetSize", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();
        
        WHEN( "CASE 1: correct size" ){
            boardManager->resetEverySlotAndSetSize(5);
            const int takenSlots = boardManager->getQuantityOfTakenSlots();
            const int boardSize = gameOptionsManager->getBoardSize();

            boardManager->resetEverySlotAndSetSize(3); // Clean-up

            THEN( "Result" ){
                REQUIRE( takenSlots == 0);
                REQUIRE( boardSize == 5);
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
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
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
            boardManager->resetSlot(Cordinates(0,0));
            int result = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( result == 0 );
            }
        }

        WHEN( "CASE 2: Reset taken slot" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->resetSlot(Cordinates(0,0));
            int result = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( result == 0 );
            }
        }

        WHEN( "CASE 3: Add two symbols, reset one" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            boardManager->resetSlot(Cordinates(0,0));
            int result = boardManager->getQuantityOfTakenSlots();
            THEN( "Result" ){
                REQUIRE( result == 1 );
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
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
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

SCENARIO( "getEveryEmptySlotCordinatesTest", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Empty board" ){
            const std::vector<Cordinates> result = boardManager->getEveryEmptySlotCordinates();
            THEN( "Result" ){
                REQUIRE( result.size() == 9 );
            }
        }

        WHEN( "CASE 2: Add one symbol" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            const std::vector<Cordinates> result = boardManager->getEveryEmptySlotCordinates();
            THEN( "Result" ){
                REQUIRE( result.size() == 8 );
            }
        }
    }
}

SCENARIO( "addNewCharacterTest", "[BoardManager]" ) {

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Correct cordinates and player" ){
            const bool result = boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            THEN( "Result" ){
                REQUIRE( result == true );
            }
        }

        WHEN( "CASE 2: Correct cordinates and player, but slot is taken" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            const bool result = boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            THEN( "Result" ){
                REQUIRE( result == false );
            }
        }

        WHEN( "CASE 3: Correct coridnates but incorrect player" ){
            int exceptionValidator = 0;
            try{
                const bool result = boardManager->addNewCharacter(Cordinates(0,1), Participant::NONE);
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
                boardManager->addNewCharacter(Cordinates(-10,0), Participant::HUMAN);
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
                boardManager->addNewCharacter(Cordinates(0,-10), Participant::HUMAN);
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
                boardManager->addNewCharacter(Cordinates(10,0), Participant::HUMAN);
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
            const Participant result = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( result == Participant::NONE );
            }
        }

        WHEN( "CASE 2: East"){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::COMPUTER);

            const Participant result = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( result == Participant::HUMAN );
            }
        }

        WHEN( "CASE 3: South"){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);

            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,2), Participant::HUMAN);

            const Participant result = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( result == Participant::COMPUTER );
            }
        }

        WHEN( "CASE 4: East-South"){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::COMPUTER);

            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,2), Participant::HUMAN);

            const Participant result = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( result == Participant::COMPUTER );
            }
        }

        WHEN( "CASE 5: West-South"){
            boardManager->addNewCharacter(Cordinates(0,2), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);

            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);

            const Participant result = boardManager->findWinner();
            THEN( "Result" ){
                REQUIRE( result == Participant::COMPUTER );
            }
        }
    }
}

SCENARIO( "findWinner, is possible to check slots", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();     

        WHEN( "CASE 1: Is possible to check EAST slots" ){
            const bool firstResult = bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(0,0));
            const bool secondResult = bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(0,1));

            int exceptionValidator1 = 0;
            try {
                bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(0,7));
            } catch ( const std::invalid_argument& e){
                exceptionValidator1++;
            }

            int exceptionValidator2 = 0;
            try{
                bridgeToTestClass.executeIsPossibleToCheckEastSlots(Cordinates(-2,0));
            } catch( const std::invalid_argument& e){
                exceptionValidator2++;
            }


            THEN( "firstResult" ){
                REQUIRE( firstResult == true );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == false );
            }
            THEN( "first exception" ){
                REQUIRE( exceptionValidator1 != 0 );
            }
            THEN( "second exception" ){
                REQUIRE( exceptionValidator2 != 0 );
            }
        }

        WHEN( "CASE 2: Is possible to check SOUTH slots" ){
            const bool firstResult = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(0,0));
            const bool secondResult = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(1,0));

            int exceptionValidator1 = 0;
            try {
                const bool thirdResult = bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(7,0));
            } catch( const std::invalid_argument& e){
                exceptionValidator1++;
            }

            int exceptionValidator2 = 0;
            try{
                bridgeToTestClass.executeIsPossibleToCheckSouthSlots(Cordinates(-2,0));
            } catch( const std::invalid_argument& e){
                exceptionValidator2++;
            }

            THEN( "firstResult" ){
                REQUIRE( firstResult == true );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == false );
            }
            THEN( "first exception" ){
                REQUIRE( exceptionValidator1 != 0 );
            }
            THEN( "second exception" ){
                REQUIRE( exceptionValidator2 != 0 );
            }
        }

        WHEN( "CASE 3: Is possible to check WEST slots" ){
            const bool firstResult = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(0,2));
            const bool secondResult = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(0,1));
            
            int exceptionValidator1 = 0;
            try {
                const bool thirdResult = bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(0,9));
            } catch ( const std::invalid_argument& e){
                exceptionValidator1++;
            }

            int exceptionValidator2 = 0;
            try{
                bridgeToTestClass.executeIsPossibleToCheckWestSlots(Cordinates(-2,0));
            }catch( const std::invalid_argument& e){
                exceptionValidator2++;
            }

            THEN( "firstResult" ){
                REQUIRE( firstResult == true );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == false );
            }
            THEN( "first exception" ){
                REQUIRE( exceptionValidator1 != 0 );
            }
            THEN( "fourthResult" ){
                REQUIRE( exceptionValidator2 != 0 );
            }
        }
    }
}

SCENARIO( "findWinner, are slots not empty", "[BoardManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        // slot at the begining has been alredy checked in diffrent function, and does not affect return value of this function.
        

        WHEN( "CASE 1: Are EAST slots not empty" ){
            Cordinates beginingCordinates(0,0);

            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            const bool firstResult = bridgeToTestClass.executeAreEastSlotsNotEmpty(beginingCordinates);

            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);
            const bool secondResult = bridgeToTestClass.executeAreEastSlotsNotEmpty(beginingCordinates);
       
            THEN( "secondResult" ){
                REQUIRE( firstResult == false );
            }
            THEN( "thirdResult" ){
                REQUIRE( secondResult == true );
            }
        }

        WHEN( "CASE 2: Are SOUTH slots not empty" ){
            Cordinates beginingCordinates(0,0);
            
            boardManager->addNewCharacter(Cordinates(1,0), Participant::COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreSouthSlotsNotEmpty(beginingCordinates);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreSouthSlotsNotEmpty(beginingCordinates);

            THEN( "secondResult" ){
                REQUIRE( firstResult == false );
            }
            THEN( "thirdResult" ){
                REQUIRE( secondResult == true );
            }
        }


        WHEN( "CASE 3: Are EAST-SOUTH slots not empty" ){
            Cordinates beginingCordinates(0,0);

            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreEastSouthSlotsNotEmpty(beginingCordinates);

            boardManager->addNewCharacter(Cordinates(2,2), Participant::COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreEastSouthSlotsNotEmpty(beginingCordinates);

            THEN( "firstResult" ){
                REQUIRE( firstResult == false );
            }
            THEN( "secondResult" ){
                REQUIRE( secondResult == true );
            }   
        }
        
        WHEN( "CASE 4: Are WEST-SOUTH slots not empty" ){
            Cordinates beginingCordinates(0,2);

            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreWestSouthSlotsNotEmpty(beginingCordinates);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::HUMAN);
            const bool secondResult = bridgeToTestClass.executeAreWestSouthSlotsNotEmpty(beginingCordinates);
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

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Are EAST slots contain win state" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);
            const bool firstResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(0,0));

            boardManager->addNewCharacter(Cordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,2), Participant::COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(1,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(0,2), Participant::COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(0,0));

            boardManager->addNewCharacter(Cordinates(1,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,2), Participant::HUMAN);
            const bool fourthResult = bridgeToTestClass.executeAreEastSlotsContainWinState(Cordinates(1,0));

            THEN( "Result" ){
                REQUIRE( firstResult  == true);
                REQUIRE( secondResult == true);

                REQUIRE( thirdResult == false);
                REQUIRE( fourthResult  == false);
            }
        }

        WHEN( "CASE 2: Are SOUTH slots contain win state" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::HUMAN);
            const bool firstResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,0));

            boardManager->addNewCharacter(Cordinates(0,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::COMPUTER);
            const bool secondResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,1));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,0));

            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::HUMAN);
            const bool fourthResult = bridgeToTestClass.executeAreSouthSlotsContainWinState(Cordinates(0,1));

            THEN( "Result" ){
                REQUIRE( firstResult  == true);
                REQUIRE( secondResult == true);

                REQUIRE( thirdResult == false);
                REQUIRE( fourthResult  == false);
            }
        }

        WHEN( "CASE 3: Are EAST-SOUTH slots contain win state" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::HUMAN);
            const bool secondResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::HUMAN);
            const bool fourthResult = bridgeToTestClass.executeAreEastSouthSlotsContainWinState(Cordinates(0,0));

            THEN( "Result" ){
                REQUIRE( firstResult  == true);
                REQUIRE( secondResult == true);

                REQUIRE( thirdResult  == false);
                REQUIRE( fourthResult == false);
            }
        }

        WHEN( "CASE 4: Are WEST-SOUTH slots contain win state" ){
            boardManager->addNewCharacter(Cordinates(0,2), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            const bool firstResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::HUMAN);
            const bool secondResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            const bool thirdResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2));

            boardManager->resetEverySlot();

            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::HUMAN);
            const bool fourthResult = bridgeToTestClass.executeAreWestSouthSlotsContainWinState(Cordinates(0,2));

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



// EAST:
const bool BoardManagerTestSuite::executeIsPossibleToCheckEastSlots(const Cordinates& CORDINATES) const{
    return boardManager->isPossibleToCheckEastSlots(CORDINATES);
}
const bool BoardManagerTestSuite::executeAreEastSlotsNotEmpty(const Cordinates& CORDINATES) const {
    return boardManager->areEastSlotsNotEmpty(CORDINATES);
}
const bool BoardManagerTestSuite::executeAreEastSlotsContainWinState(const Cordinates& CORDINATES) const{
    return boardManager->areEastSlotsContainWinState(CORDINATES);
}

// SOUTH:
const bool BoardManagerTestSuite::executeIsPossibleToCheckSouthSlots(const Cordinates& CORDINATES) const{
    return boardManager->isPossibleToCheckSouthSlots(CORDINATES);
}
const bool BoardManagerTestSuite::executeAreSouthSlotsNotEmpty(const Cordinates& CORDINATES) const{
    return boardManager->areSouthSlotsNotEmpty(CORDINATES);
}
const bool BoardManagerTestSuite::executeAreSouthSlotsContainWinState(const Cordinates& CORDINATES) const{
    return boardManager->areSouthSlotsContainWinState(CORDINATES);
}

// EAST-SOUTH
const bool BoardManagerTestSuite::executeAreEastSouthSlotsNotEmpty(const Cordinates& CORDINATES) const{
    return boardManager->areEastSouthSlotsNotEmpty(CORDINATES);
}
const bool BoardManagerTestSuite::executeAreEastSouthSlotsContainWinState(const Cordinates& CORDINATES) const{
    return boardManager->areEastSouthSlotsContainWinState(CORDINATES);
}

// WEST-SOUTH:
const bool BoardManagerTestSuite::executeIsPossibleToCheckWestSlots(const Cordinates& CORDINATES) const{
    return boardManager->isPossibleToCheckWestSlots(CORDINATES);
}
const bool BoardManagerTestSuite::executeAreWestSouthSlotsNotEmpty(const Cordinates& CORDINATES) const{
    return boardManager->areWestSouthSlotsNotEmpty(CORDINATES);
}
const bool BoardManagerTestSuite::executeAreWestSouthSlotsContainWinState(const Cordinates& CORDINATES) const{
    return boardManager->areWestSouthSlotsContainWinState(CORDINATES);
}
    