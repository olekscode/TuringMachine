#include <iostream>

#include "turingmachine.h"

using namespace std;

int main(int argc, char* argv[])
{
    try {
        TuringMachine TM1;
        TM1.loadInstructionsFromFile("instructions.txt");

        TM1.setTape(argv[1]);
        TM1.run();
        cout << TM1.showTape() << endl;

        return 0;
    }
    catch(Exception *e) {
        cout << e->what() << endl;
    }
}

