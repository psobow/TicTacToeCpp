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
SCENARIO( "executeTheBestComputerMove", "[MinMaxManager]" ){

    GIVEN( "MinMaxManager, BoardManager, Bridge initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        MinMaxManager *minMaxManager = MinMaxManager::getInstance();
        MinMaxManagerTestSuite bridgeToTestClass;

        WHEN( "CASE 1: Empty board" ){
            minMaxManager->executeTheBestComputerMove();

            THEN( "Result" ){
                REQUIRE( bridgeToTestClass.getTheBestMove().equals(Cordinates(0,0)) );
            }
        }

        WHEN( "CASE 2: ") {
            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,2), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,2), PLAYER);

            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,1), COMPUTER);

            minMaxManager->executeTheBestComputerMove();

            THEN( "Result" ){ // expected move Cordinates (0,2)
                REQUIRE( bridgeToTestClass.getTheBestMove().equals(Cordinates(0,2)) );
            }
        }

        WHEN( "CASE 3: ") { // computer will lose in next oponent move in every case. expcted move is first empty slot
            boardManager->addNewSymbol(Cordinates(0,2), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(1,1), PLAYER);

            minMaxManager->executeTheBestComputerMove();

            THEN( "Result" ){ // expected move Cordinates (0,1)
                REQUIRE( bridgeToTestClass.getTheBestMove().equals(Cordinates(0,1)) );
            }
        }
    }
}



SCENARIO( "scoreGameFromComputerPOV", "[MinMaxManager]" ){
    // findWinner algorithm required at least 5 taken slots on 3x3 board to search for winner

    GIVEN( "MinMaxManager, BoardManager, Bridge initialization, Clean up board" ) {
        BoardManager *boardManager = BoardManager::getInstance();
        boardManager->resetEverySlot();
        MinMaxManagerTestSuite bridgeToTestClass;

        WHEN( "CASE 1: Board contatin win state for Computer" ){
            boardManager->addNewSymbol(Cordinates(0,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(0,1), COMPUTER);
            boardManager->addNewSymbol(Cordinates(0,2), COMPUTER);

            boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,1), PLAYER);

            const int depth = 1;
            const int result = bridgeToTestClass.scoreGameFromComputerPOV(depth);

            THEN( "Result" ){
                REQUIRE( result == 999 );
            }
        }

        WHEN( "CASE 2: Board contatin win state for Player" ){
            boardManager->addNewSymbol(Cordinates(0,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,2), PLAYER);

            boardManager->addNewSymbol(Cordinates(2,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(2,1), COMPUTER);

            const int depth = 1;
            const int result = bridgeToTestClass.scoreGameFromComputerPOV(depth);

            THEN( "Result" ){
                REQUIRE( result == -999 );
            }
        }

        WHEN( "CASE 3: Board does not contatin win state" ){
            boardManager->addNewSymbol(Cordinates(0,0), COMPUTER);
            boardManager->addNewSymbol(Cordinates(0,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(0,2), COMPUTER);

            boardManager->addNewSymbol(Cordinates(2,0), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,1), PLAYER);
            boardManager->addNewSymbol(Cordinates(2,2), COMPUTER);

            const int depth = 1;
            const int result = bridgeToTestClass.scoreGameFromComputerPOV(depth);

            THEN( "Result" ){
                REQUIRE( result == 0 );
            }
        }
    }
}


SCENARIO( "get Min & Max value index", "[MinMaxManager]" ){

    GIVEN( "Bridge and vector initialization" ) {
        MinMaxManagerTestSuite BridgeToTestClass;
        const std::vector<int> testVector{0,1,2,3,4,5};

        WHEN( "CASE 1: get MIN value index" ){
            const int result = BridgeToTestClass.getMinValueIndex(testVector);
            THEN( "Result" ){
                REQUIRE( result == 0 );
            }
        }

        WHEN( "CASE 2: get MAX value index" ){
            const int result = BridgeToTestClass.getMaxValueIndex(testVector);
            THEN( "Result" ){
                REQUIRE( result == 5 );
            }
        }
    }
}


const int MinMaxManagerTestSuite::scoreGameFromComputerPOV(const int depth) const{
    return minMaxManager->scoreGameFromComputerPOV(depth);
}

const int MinMaxManagerTestSuite::calculateTheBestMove(const SymbolEnum& turnTakingPlayer, int depth){
    return minMaxManager->calculateTheBestMove(turnTakingPlayer, depth);
}

const int MinMaxManagerTestSuite::getMaxValueIndex(const std::vector<int>& vec) const{
    return minMaxManager->getMaxValueIndex(vec);
}
const int MinMaxManagerTestSuite::getMinValueIndex(const std::vector<int>& vec) const{
    return minMaxManager->getMinValueIndex(vec);
}

const Cordinates& MinMaxManagerTestSuite::getTheBestMove() const{
    return minMaxManager->theBestMoveCordinates;
}