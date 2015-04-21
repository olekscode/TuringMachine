#include "tape.h"

Tape::Tape()
    : mSize(0), mOffset(0)
{
    mTape = new char[0];
}

void Tape::setText(const char* pText, int pSize, int pInitPos)
{
    mTape = new char[pSize + 1];
    mTape[pSize] = '\0';

    for (int i = 0; i < pSize; ++i) {
        mTape[i] = pText[i];
    }

    mSize = pSize;
    mOffset = pInitPos;
}

char& Tape::operator [] (int pIndex)
{
    pIndex = pIndex + mOffset;

    if (pIndex < 0) {
        int lNewSize = mSize - pIndex;
        char* lNewTape = new char[lNewSize + 1];
        lNewTape[lNewSize] = '\0';

        for (int i = 0; i < -pIndex; ++i) {
            lNewTape[i] = 'E';
        }

        for (int i = -pIndex; i < lNewSize; ++i) {
            lNewTape[i] = mTape[i + pIndex];
        }

        mTape = lNewTape;
        mSize = lNewSize;
        mOffset += -pIndex;

        pIndex = 0;
    }
    else if (pIndex >= mSize) {
        char* lNewTape = new char[pIndex + 2];
        lNewTape[pIndex + 1] = '\0';

        for (int i = 0; i < mSize; ++i) {
            lNewTape[i] = mTape[i];
        }

        for (int i = mSize; i < pIndex + 1; ++i) {
            lNewTape[i] = 'E';
        }

        mTape = lNewTape;
        mSize = pIndex + 1;
    }
    else {
        shrinkToFit(pIndex);
    }

    return mTape[pIndex];
}

const char* Tape::getText()
{
    return mTape;
}

int Tape::getSize() const
{
    return mSize;
}

int Tape::getOffset() const
{
    return mOffset;
}

void Tape::shrinkToFit(int &pIndex)
{
    int lNumOfFirstEmptyCells = 0;
    int lNumOfLastEmptyCells = 0;

    for (int i = 0; i < mSize; ++i) {
        if (mTape[i] == 'E')
            ++lNumOfFirstEmptyCells;
        else
            break;
    }

    for (int i = mSize - 1; i >= 0; --i) {
        if (mTape[i] == 'E')
            ++lNumOfLastEmptyCells;
        else
            break;
    }

    int lNewBegin = lNumOfFirstEmptyCells;
    int lNewEnd = mSize - lNumOfLastEmptyCells;

    if (lNumOfFirstEmptyCells + lNumOfLastEmptyCells != 0
          && pIndex >= lNewBegin
          && pIndex < lNewEnd)
    {
        int lNewSize = lNewEnd - lNewBegin;
        char* lNewTape = new char[lNewSize + 1];
        lNewTape[lNewSize] = '\0';

        for (int i = lNewBegin; i < lNewEnd; ++i) {
            lNewTape[i - lNewBegin] = mTape[i];
        }

        mTape = lNewTape;
        mSize = lNewSize;
        mOffset -= lNumOfFirstEmptyCells;

        pIndex -= lNumOfFirstEmptyCells;
    }
}
