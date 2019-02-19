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
g++ -c ./tests/GameManagerTestSuite.cpp

#move file into object directory
mv GameManagerTestSuite.o ./object/tests

#link compiled files into test
g++ -std=c++11 -o ./output/GameManagerTestSuite.out \
./object/tests/ProvideMain.o ./object/tests/GameManagerTestSuite.o

#start test
echo
echo Starting Game Manager Test Suite...
./output/GameManagerTestSuite.out
echo
echo Finished Game Manager Test.
echo ============================
echo