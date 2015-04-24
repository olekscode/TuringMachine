#include "head.h"

TapeCell* Head::getCurrCell() const
{
    return mCurrCell;
}

void Head::move(TapeCell* pNewCell)
{
    mCurrCell = pNewCell;
}

char Head::read() const
{
    if (mCurrCell == nullptr)
        throw new HeadPositionUndefined;

    return mCurrCell->value;
}

void Head::write(char pChar)
{
    if (mCurrCell == nullptr)
        throw new HeadPositionUndefined;

    mCurrCell->value = pChar;
}

