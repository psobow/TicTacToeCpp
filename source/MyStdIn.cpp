#include "../header/MyStdIn.hh"




const int MyStdIn::readNextInt(){
    int number = 0;
    std::string inputLine;
    bool isValid;

    do {
        isValid = true;
        std::getline(std::cin, inputLine);
        try {
            number = std::stoi(inputLine);
        } catch (const std::exception& e) {
            std::cerr << "ERROR. The entered number must be an integer.\n";
            isValid = false;
        }
    } while (isValid == false);

    return number;
}

const int MyStdIn::readNextIntFromValidScope(const int bottom, const int top){
    int number = 0;
    std::string inputLine;
    bool isValid;

    do {
        isValid = true;
        number = readNextInt();
        if(number < bottom || number > top){
            std::cerr << "ERROR. The entered number must be integer from " << bottom << " to " << top << ".\n";
            isValid = false;
        }

    } while (isValid == false);

    return number;
}

const char MyStdIn::readNextCharWithValidation(std::vector<char> validChars) {
    std::string inputLine;
    bool isValid;

    do{
        isValid = true;
        std::getline(std::cin, inputLine);
        if ( isVectorContainChar(validChars, inputLine[0]) == false ){
            std::cerr << "ERROR. The entered char must be one of this: [ ";
            for (int i = 0; i < validChars.size(); i++){
                std::cerr << validChars[i] << " ";
            }
            std::cerr << "].\n";
            isValid = false;
        }
    } while (isValid == false);

    return inputLine[0];
}

const bool MyStdIn::isVectorContainChar(std::vector<char> vec, const char character){
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] == character){
            return true;
        }
    }
    return false;
}