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
g++ -c ./tests/HelloTest.cpp

#move file into object directory
mv HelloTest.o ./object/tests

#link compiled files into test
g++ -std=c++11 -o ./output/HelloTest.out \
./object/tests/ProvideMain.o ./object/tests/HelloTest.o

#start test
./output/HelloTest.out