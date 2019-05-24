# Tic-Tac-Toe
Classic Tic-Tac-Toe console game implemented in C++ with artificial intelligence which is using [minimax](https://en.wikipedia.org/wiki/Minimax) algorithm with Alpha & Beta pruning and depth limiting to calculate the best possible move in given position with the most efficient time performance.

## Building application

1. Download Premake 5.0 from this [website](https://premake.github.io/download.html#v5) and place it somewhere where you will be able to use it from the command line. 
2. Open command line and navigate to the directory where you have `git clone` Tic-Tac-Toe game.

**Building on Windows**
- Then You should run the following command: `premake5 vs2017`. This will generate Visual studio 2017 solution inside `premake-generated-files` directory.

**Building on Linux**
- Then You should run the following command: `premake5 gmake`. This will generate a makefile for your system inside `premake-generated-files` directory.
- Then go into `premake-generated-files` with command: `cd premake-generated-files`.
- Then type `make` and hit enter for debug configuration, or `make config=release` for release configuration. This will generate `build` directory with-in ready to run executable file.

## Resources that I have found helpful:
https://www.neverstopbuilding.com/blog/minimax

https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-4-alpha-beta-pruning/

https://www.cs.cornell.edu/courses/cs312/2002sp/lectures/rec21.htm

https://www.youtube.com/watch?v=STjW3eH0Cik