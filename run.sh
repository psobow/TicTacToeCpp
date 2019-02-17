#!/bin/bash
clear

echo Hello, Bash!

#create directory if do not exist
mkdir -p object

#remove old files
rm ./object/*

#compile game
g++ -c source/*

#compile for debbuger (this line will create file a.out for debbuger) 
g++ -g source/*

#move .o files into object directory
mv SymbolManager.o ./object
mv Cordinates.o ./object
mv BoardManager.o ./object
mv GameManager.o ./object
mv MinMaxManager.o ./object
mv Main.o ./object

#link compiled files into game
g++ -std=c++11 -o game.out \
./object/SymbolManager.o \
./object/Cordinates.o \
./object/BoardManager.o \
./object/GameManager.o \
./object/MinMaxManager.o \
./object/Main.o 

./game.out