#ifndef MY_STD_IN_H
#define MY_STD_IN_H

#include <iostream>
#include <vector>

class MyStdIn {
public:
    const static int readNextInt();
    const static int readNextIntFromValidScope(const int bottom, const int top);
    const static char readNextCharWithValidation(std::vector<char> validChars);

private:
    const static bool isVectorContainChar(std::vector<char> vec, const char character);
};

#endif