#!/bin/bash


#create directory if do not exist
mkdir -p ./object
cd ./object
mkdir -p tests
cd ..

#if file ProvideMain.o do not exist compile it
if [ ! -f ./object/tests/ProvideMain.o ]; then
    sh ./runProvideMain.sh
fi

#compile test
g++ -c ./tests/SymbolManagerTestSuite.cpp

#move file into object directory
mv SymbolManagerTestSuite.o ./object/tests

#link compiled files into test
g++ -std=c++11 -o ./output/SymbolManagerTestSuite.out \
./object/tests/ProvideMain.o ./object/tests/SymbolManagerTestSuite.o

#start test
echo
echo Starting Symbol Manager Test Suite...
./output/SymbolManagerTestSuite.out
echo
echo Finished Symbol Manager Test.
echo ============================
echo