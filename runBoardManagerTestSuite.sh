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
g++ -c ./tests/BoardManagerTestSuite.cpp

#move file into object directory
mv BoardManagerTestSuite.o ./object/tests

#link compiled files into test
g++ -std=c++11 -o ./output/BoardManagerTestSuite.out \
./object/tests/ProvideMain.o ./object/tests/BoardManagerTestSuite.o


#start test
echo
echo Starting Board Manager Test Suite...
./output/BoardManagerTestSuite.out
echo
echo Finished Board Manager Test.
echo ============================
echo