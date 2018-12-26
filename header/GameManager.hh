#include <iostream>

enum MenuEnum {
    PLAY,
    OPTIONS,
    EXIT
};

class GameManager
{
    private:
       

    public:
        GameManager();
        ~GameManager();

        void printMenu();
        void getValidDecision();
        void executeMenuDecision(MenuEnum menuEnum);
};