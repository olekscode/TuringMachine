#ifndef HEAD_H
#define HEAD_H

#include "exception.h"
#include "tape.h"

class Head
{
    TapeCell* mCurrCell;

public:
    Head() = default;

    TapeCell* getCurrCell() const;
    void move(TapeCell* pNewCell);

    char read() const;
    void write(char pChar);
};

#endif // HEAD_H
