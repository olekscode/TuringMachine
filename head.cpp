#include "head.h"

void Head::moveTo(char *pSymbol)
{
    mCurrSymbol = pSymbol;
}

char Head::read() const
{
    if (mCurrSymbol == nullptr)
        throw new HeadPositionUndefined;

    return *mCurrSymbol;
}

void Head::write(char pChar)
{
    if (mCurrSymbol == nullptr)
        throw new HeadPositionUndefined;

    *mCurrSymbol = pChar;
}

