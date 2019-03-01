#include <iostream>
#include "../header/BoardManager.hh"
#include "../header/GameManager.hh"
#include "../header/Cordinates.hh"
#include "../header/MinMaxManager.hh"
#include "../header/MyStdIn.hh"


int main() 
{
    std::cout << "Hello, World!\n" << std::endl;

    std::vector<char> validChars {'y', 'Y', 'n', 'N'};
    char x = MyStdIn::readNextCharWithValidation(validChars);
    std::cout << x << "\n";
    return 0;
}


/*
materiały:

https://www.neverstopbuilding.com/blog/minimax

https://www.youtube.com/watch?v=STjW3eH0Cik


*/