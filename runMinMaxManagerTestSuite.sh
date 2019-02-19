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
g++ -c ./tests/MinMaxManagerTestSuite.cpp

#move file into object directory
mv MinMaxManagerTestSuite.o ./object/tests

#link compiled files into test
g++ -std=c++11 -o ./output/MinMaxManagerTestSuite.out \
./object/tests/ProvideMain.o ./object/tests/MinMaxManagerTestSuite.o

#start test
echo
echo Starting MinMax Manager Test Suite...
./output/MinMaxManagerTestSuite.out
echo 
echo Finished MinMax Manager Test.
echo ============================
echo