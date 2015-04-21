#ifndef PROCESSINGUNIT_H
#define PROCESSINGUNIT_H

#include <vector>

#include "head.h"
#include "tape.h"
#include "instruction.h"

class ProcessingUnit
{
    Head *mHead;
    Tape *mTape;

    int mCurrHeadPosition;
    unsigned mCurrState;

    std::vector<Instruction>* mInstructions;

public:
    ProcessingUnit(Head *pHead, Tape *pTape,
                   std::vector<Instruction>* pInstructions);

    void step();
    unsigned getState() const;
    int getCurrHeadPosition() const;

private:
    void moveHeadLeft();
    void moveHeadRight();

    RightHandInstr lookForInstruction() const;
    void executeInstruction(RightHandInstr pRight);
};

#endif // PROCESSINGUNIT_H
