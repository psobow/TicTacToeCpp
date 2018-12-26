#!/bin/bash
clear

echo Hello Bash!

rm ./object/SymbolManager.o
rm ./object/BoardManager.o
rm ./object/GameManager.o
rm ./object/Main.o
rm game

g++ -c source/SymbolManager.cpp
g++ -c source/BoardManager.cpp
g++ -c source/GameManager.cpp
g++ -c source/Main.cpp

mv SymbolManager.o ./object
mv BoardManager.o ./object
mv GameManager.o ./object
mv Main.o ./object

g++ -o game ./object/SymbolManager.o ./object/BoardManager.o ./object/GameManager.o ./object/Main.o

./game