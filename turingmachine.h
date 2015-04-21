#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "head.h"
#include "processingunit.h"
#include "tape.h"
#include "instruction.h"

using namespace std;

class TuringMachine
{
    Head *mHead;
    Tape *mTape;
    ProcessingUnit *mProcessingUnit;

    std::vector<Instruction> mInstructions;

public:
    TuringMachine();
    ~TuringMachine();

    void loadInstructionsFromFile(std::string pPath);
    void setTape(std::string pText);
    void run();

    std::string showTape() const;
};

#endif // TURINGMACHINE_H
