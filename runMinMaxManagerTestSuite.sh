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
g++ -c ./tests/MinMaxManagerTestSuite.cpp
g++ -c ./source/BoardManager.cpp
g++ -c ./source/Cordinates.cpp
g++ -c ./source/GameOptionsManager.cpp
g++ -c ./source/MinMaxManager.cpp

#move file into object directory
mv MinMaxManagerTestSuite.o ./object/tests
mv BoardManager.o ./object
mv Cordinates.o ./object
mv GameOptionsManager.o ./object
mv MinMaxManager.o ./object

#link compiled files into test
g++ -std=c++11 -o ./output/MinMaxManagerTestSuite.out \
./object/tests/ProvideMain.o ./object/tests/MinMaxManagerTestSuite.o \
./object/BoardManager.o \
./object/Cordinates.o \
./object/GameOptionsManager.o \
./object/MinMaxManager.o \

#start test
echo
echo Starting MinMax Manager Test Suite...
./output/MinMaxManagerTestSuite.out
echo 
echo Finished MinMax Manager Tests.
echo ============================
echo