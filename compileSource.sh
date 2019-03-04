#!/bin/bash
clear

#create directory if do not exist
mkdir -p object
mkdir -p output

#compile game
g++ -c source/*.cpp

#compile for debuger (next line will create file a.out for debbuger) 
g++ -g source/*.cpp
mv a.out debug.out
mv debug.out ./output

#move every .o files into object directory
mv *.o ./object

echo Compilation finished.