#include "processingunit.h"

ProcessingUnit::ProcessingUnit(Head *pHead, Tape *pTape,
                               std::vector<Instruction>* pInstructions)
    : mHead(pHead), mTape(pTape),
      /*mCurrHeadPosition(0),*/ mCurrState(0),
      mInstructions(pInstructions)
{
    mHead->move(pTape->getInit());
}

void ProcessingUnit::moveHeadLeft()
{
    // TODO: consider optimizing this approach
    mHead->move(mTape->getLeft(mHead->getCurrCell()));
}

void ProcessingUnit::moveHeadRight()
{
    // TODO: consider optimizing this approach
    mHead->move(mTape->getRight(mHead->getCurrCell()));
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
