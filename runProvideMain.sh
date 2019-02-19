#!/bin/bash


#compile
g++ -c ./tests/ProvideMain.cpp

#move file into object directory
mv ProvideMain.o ./object/tests