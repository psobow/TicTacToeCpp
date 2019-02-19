#!/bin/bash
clear

echo Hello, Bash!

#create directory if do not exist
mkdir -p object

#compile game
g++ -c source/*.cpp

#compile for debuger (next line will create file a.out for debbuger) 
g++ -g source/*.cpp
mv a.out debug.out
mv debug.out ./output

#move every .o files into object directory
mv *.o ./object

#link compiled files into game
g++ -std=c++11 -o ./output/game.out \
./object/*.o

#start program
./output/game.out