#include "processingunit.h"

ProcessingUnit::ProcessingUnit(Head *pHead, Tape *pTape,
                               std::vector<Instruction>* pInstructions)
    : mHead(pHead), mTape(pTape),
      mCurrHeadPosition(0), mCurrState(0),
      mInstructions(pInstructions)
{
    mHead->moveTo(&(*pTape)[0]);
}

void ProcessingUnit::moveHeadLeft()
{
    mHead->moveTo(&(*mTape)[--mCurrHeadPosition]);
}

void ProcessingUnit::moveHeadRight()
{
    mHead->moveTo(&(*mTape)[++mCurrHeadPosition]);
}

RightHandInstr ProcessingUnit::lookForInstruction() const
{
    LeftHandInstr left;

    for (std::vector<Instruction>::iterator iter = mInstructions->begin();
         iter != mInstructions->end(); ++iter)
    {
        left = iter->leftHand;
        if (left.state == mCurrState && left.symbol == mHead->read()) {
            return iter->rightHand;
        }
    }
    // TODO: return sth here
    // IDEA: throw an exception informing user that his algorithm sucks
}

void ProcessingUnit::executeInstruction(RightHandInstr pRight)
{
    mHead->write(pRight.symbol);
    mCurrState = pRight.state;

    if (pRight.shift == L) moveHeadLeft();
    else if (pRight.shift == R) moveHeadRight();
}

void ProcessingUnit::step()
{
    RightHandInstr right = lookForInstruction();
    executeInstruction(right);
}

unsigned ProcessingUnit::getState() const
{
    return mCurrState;
}

int ProcessingUnit::getCurrHeadPosition() const
{
    return mCurrHeadPosition;
}
