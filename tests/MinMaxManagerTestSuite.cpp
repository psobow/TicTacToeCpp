#include "../../libs/catch.hpp"
#include "MinMaxManagerTestSuite.hh"


/* TEST TEMPLATE

SCENARIO( "", "[MinMaxManager]" ){

    GIVEN( "MinMaxManager, BoardManager initialization, Clean up board" ) {
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
static MinMaxManager *minMaxManager = MinMaxManager::getInstance();
static MinMaxManagerTestSuite bridgeToTestClass;


SCENARIO( "executeTheBestComputerMove", "[MinMaxManager]" ){

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();
        
        WHEN( "CASE 1: Empty board" ){
            minMaxManager->executeTheBestComputerMove();

            THEN( "Result" ){
                REQUIRE( bridgeToTestClass.getTheBestMove().equals(Cordinates(0,0)) );
            }
        }

        WHEN( "CASE 2: ") {
            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,2), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::HUMAN);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::COMPUTER);

            minMaxManager->executeTheBestComputerMove();

            THEN( "Result" ){ // expected move Cordinates (0,2)
                REQUIRE( bridgeToTestClass.getTheBestMove().equals(Cordinates(0,2)) );
            }
        }

        WHEN( "CASE 3: ") { // computer will lose in next oponent move in every case. expcted move is first empty slot
            boardManager->addNewCharacter(Cordinates(0,2), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(1,1), Participant::HUMAN);

            minMaxManager->executeTheBestComputerMove();

            THEN( "Result" ){ // expected move Cordinates (0,1)
                REQUIRE( bridgeToTestClass.getTheBestMove().equals(Cordinates(0,1)) );
            }
        }
    }
}



SCENARIO( "scoreGameFromComputerPOV", "[MinMaxManager]" ){
    // findWinner algorithm required at least 5 taken slots on 3x3 board to search for winner

    GIVEN( "Clean up board" ) {
        boardManager->resetEverySlot();

        WHEN( "CASE 1: Board contatin win state for Computer" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(0,2), Participant::COMPUTER);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::HUMAN);

            const int DEPTH = 1;
            const int RESULT = bridgeToTestClass.scoreGameFromComputerPOV(DEPTH);

            THEN( "Result" ){
                REQUIRE( RESULT == 999 );
            }
        }

        WHEN( "CASE 2: Board contatin win state for Player" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,2), Participant::HUMAN);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::COMPUTER);

            const int DEPTH = 1;
            const int RESULT = bridgeToTestClass.scoreGameFromComputerPOV(DEPTH);

            THEN( "Result" ){
                REQUIRE( RESULT == -999 );
            }
        }

        WHEN( "CASE 3: Board does not contatin win state" ){
            boardManager->addNewCharacter(Cordinates(0,0), Participant::COMPUTER);
            boardManager->addNewCharacter(Cordinates(0,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(0,2), Participant::COMPUTER);

            boardManager->addNewCharacter(Cordinates(2,0), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,1), Participant::HUMAN);
            boardManager->addNewCharacter(Cordinates(2,2), Participant::COMPUTER);

            const int DEPTH = 1;
            const int RESULT = bridgeToTestClass.scoreGameFromComputerPOV(DEPTH);

            THEN( "Result" ){
                REQUIRE( RESULT == 0 );
            }
        }
    }
}


SCENARIO( "get Min & Max value index", "[MinMaxManager]" ){

    GIVEN( "Vector initialization" ) {
        const std::vector<int> EXAMPLE_VECTOR {0,1,2,3,4,5};

        WHEN( "CASE 1: get MIN value index" ){
            const int RESULT = bridgeToTestClass.getMinValueIndex(EXAMPLE_VECTOR);
            THEN( "Result" ){
                REQUIRE( RESULT == 0 );
            }
        }

        WHEN( "CASE 2: get MAX value index" ){
            const int RESULT = bridgeToTestClass.getMaxValueIndex(EXAMPLE_VECTOR);
            THEN( "Result" ){
                REQUIRE( RESULT == 5 );
            }
        }
    }
}


const int MinMaxManagerTestSuite::scoreGameFromComputerPOV(const int DEPTH) const{
    return minMaxManager->scoreGameFromComputerPOV(DEPTH);
}

const int MinMaxManagerTestSuite::calculateTheBestMoveFor(const Participant& TURN_TAKING_PLAYER, int depth){
    return minMaxManager->calculateTheBestMoveFor(TURN_TAKING_PLAYER, depth);
}

const int MinMaxManagerTestSuite::getMaxValueIndex(const std::vector<int>& VEC) const{
    return minMaxManager->getMaxValueIndex(VEC);
}
const int MinMaxManagerTestSuite::getMinValueIndex(const std::vector<int>& VEC) const{
    return minMaxManager->getMinValueIndex(VEC);
}

const Cordinates& MinMaxManagerTestSuite::getTheBestMove() const{
    return minMaxManager->theBestMoveCordinates;
}