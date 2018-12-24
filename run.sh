#!/bin/bash
clear

echo Hello Bash!

rm ./object/Board.o
rm ./object/Game.o
rm ./object/Main.o
rm game

g++ -c source/Main.cpp
g++ -c source/Board.cpp
g++ -c source/Game.cpp

mv Main.o ./object
mv Board.o ./object
mv Game.o ./object

g++ -o game ./object/Main.o ./object/Board.o ./object/Game.o

./game