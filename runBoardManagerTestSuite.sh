#!/bin/bash


#create directory if do not exist
mkdir -p output
mkdir -p object
cd ./object
mkdir -p tests
cd ..

#if file ProvideMain.o do not exist create it
if [ ! -f ./object/tests/ProvideMain.o ]; then
    sh ./runProvideMain.sh
fi

#compile files that are required for test
g++ -c ./tests/BoardManagerTestSuite.cpp
g++ -c ./source/BoardManager.cpp
g++ -c ./source/GameOptionsManager.cpp
g++ -c ./source/Cordinates.cpp

#move files into object directory
mv BoardManagerTestSuite.o ./object/tests
mv BoardManager.o ./object
mv GameOptionsManager.o ./object
mv Cordinates.o ./object

#link compiled files into test
g++ -std=c++11 -o ./output/BoardManagerTestSuite.out \
./object/tests/ProvideMain.o ./object/tests/BoardManagerTestSuite.o \
./object/BoardManager.o \
./object/GameOptionsManager.o \
./object/Cordinates.o


#start test
echo
echo Starting Board Manager Test Suite...
./output/BoardManagerTestSuite.out
echo
echo Finished Board Manager Tests.
echo ============================
echo